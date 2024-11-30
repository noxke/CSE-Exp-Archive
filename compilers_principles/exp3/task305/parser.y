%locations
//bison的.y文件中，加入％locations，这样bison加入－d编译后的.h符号表文件中会多出一个YYLTYPE结构体定义和一个该结构体类型的全局变量yylloc，这样，flex的.l文件include该.h文件后，该结构体类型就可以被flex知道，且flex可以向yylloc里面填入信息。

%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "def.h"

#include <bits/stdc++.h>
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
char myerror[255];
extern NProgram *p;
extern int allerror;
void myyyerror();

extern "C"{
void yyerror(const char* fmt, ...);
extern int yylex(void);
}
%}

%union {
		NExtDefFunDec  *nExtDefFunDec;
        NExtDefList *nExtDefList;
        NExtDef *nExtDef;
        NSpecifier *nSpecifier;
        NExtDecList *nExtDecList;
        NDecList *nDecList;
        NVarDec *nVarDec;
        NFunDec *nFunDec;
        NCompSt *nCompSt;
        NVarList *nVarList;
        NParamDec *nParamDec;
        NDefList *nDefList;
        NDec *nDec;
        NDef *nDef;
        NStmtList *nStmtList;
        NStmt *nStmt;
        NExpression *nExpression;
        NArgs *nArgs;
        NIdentifier *nIdentifier;
        NStructSpecifier *nStructSpecifier;

        std::string *text;
		int		type_int;
        int		line;
		float	type_float;
		int		type_char;
		char	type_id[32];
}
//union的默认结构体类型为YYSTYPE，相当于自己把YYSTYPE重新定义为union类型。所以相应的yylval也变为union类型。
//这个union类型-d选项编译时会放在头文件中
//  %type 定义非终结符的语义值类型
%type  <nExtDefFunDec> program
%type  <nExtDefList> ExtDefList
%type  <nExtDef> ExtDef
%type  <nSpecifier> Specifier
%type  <nExtDecList> ExtDecList
%type  <nDecList> DecList
%type  <nVarDec> VarDec
%type  <nFunDec> FunDec
%type  <nCompSt> CompSt

%type  <nDefList> DefList
%type  <nVarList> VarList
%type  <nParamDec> ParamDec
%type  <nDec> Dec
%type  <nDef> Def
%type  <nStmtList> StmtList

%type  <nExpression> Exp
%type  <nStmt> Stmt
%type  <nArgs> Args
%type  <nIdentifier> OptTag  Tag
%type  <nStructSpecifier> StructSpecifier
//% token 定义终结符的语义值类型
%token <type_int> INT                   //指定INT的语义值是type_int，有词法分析得到的数值
%token <type_id> ID RELOP TYPE    //指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串mmecpy得到的
%token <type_float> FLOAT               //指定ID的语义值是type_float，有词法分析得到的float
%token <type_char> CHAR
%token <line> STRUCT LP RP LC RC LB RB SEMI COMMA     //用bison对该文件编译时，带参数-d，生成的exp.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码
%token <line> DOT PLUS MINUS STAR DIV MOD ASSIGNOP AND OR NOT IF BREAK ELSE WHILE RETURN PLUSASS MINUSASS STARASS DIVASS MODASS PLUSPLUS MINUSMINUS
//由低到高的定义优先级

%left COMMA
%left ASSIGNOP PLUSASS MINUSASS STARASS DIVASS MODASS
//先不支持？三目运算
%left OR
%left AND
%left RELOP//比较运算内部暂不定义优先级
%left PLUS MINUS
%left STAR DIV MOD
%right UMINUS NOT UPLUSPLUS UMINUSMINUS
%left PLUSPLUS MINUSMINUS 
%right DOT
%left LB

%nonassoc LOWER_THEN_ELSE //无结合性
%nonassoc ELSE

%%
/*High-level Definitions*/
program:
    ExtDefList {p=new NProgram($1);if($1) p->line=$1->line;} /*显示语法树*/
    ;
ExtDefList: {$$=nullptr;}
    | ExtDef ExtDefList {$$=new NExtDefList(*$1, $2); $$->line=$1->line;}
    ;
ExtDef:
    Specifier ExtDecList SEMI {$$=new NExtDef(*$1, $2); $$->line=$1->line;}
    | Specifier SEMI {$$=new NExtDef(*$1); $$->line=$1->line;} 
    | Specifier FunDec CompSt {$$=new NExtDef(*$1, $2, $3); $$->line=$1->line;}
    ;
ExtDecList:
    VarDec {$$=new NExtDecList(*$1, nullptr); $$->line=yylineno;}
    | VarDec COMMA ExtDecList {$$=new NExtDecList(*$1, $3); $$->line=yylineno;}
    ;

/*Specifiers*/
Specifier:
    TYPE {$$=new NSpecifier(*(new std::string($1))); $$->line=yylineno;}   
    | StructSpecifier {$$=new NSpecifier($1); $$->line=$1->line;}   
    ;

StructSpecifier:
    STRUCT OptTag LC DefList RC {$$=new NStructSpecifier($2, $4); $$->line=$1; $2->line=$1;}   
    | STRUCT Tag {$$=new NStructSpecifier($2); $$->line=$1; $2->line=$1;}
    ;

OptTag: {$$=nullptr;} 
    |ID {$$=new NIdentifier(*(new std::string($1))); $$->type="OptTag";}  
    ;

Tag:
    ID {$$=new NIdentifier(*(new std::string($1))); $$->type="Tag";}   
    ;

/*Declarators*/
VarDec:
    ID {$$=new NVarDec(*(new NIdentifier(*(new std::string($1))))); $$->line=yylineno;}   //ID结点，标识符符号串存放结点的type_id
    | VarDec LB INT RB {$$=new NVarDec(*$1); $$->line=yylineno;}
    ;
FunDec:
    ID LP VarList RP {$$=new NFunDec(*(new NIdentifier(*(new std::string($1)))), $3); $$->line=yylineno;}
    | ID LP RP {$$=new NFunDec(*(new NIdentifier(*(new std::string($1)))), nullptr); $$->line=yylineno;}
    ;
VarList:
    ParamDec {$$=new NVarList(*$1, nullptr); $$->line=yylineno;}
    | ParamDec COMMA VarList {$$=new NVarList(*$1, $3); $$->line=yylineno;}
    ;
ParamDec:
    Specifier VarDec {$$=new NParamDec(*$1, *$2); $$->line=yylineno;}
    ;

/*Statements*/
CompSt:
    LC DefList StmtList RC {$$=new NCompSt($2, $3); $$->line=$1;}
    ;
StmtList: {$$=nullptr;}  
    | Stmt StmtList  {$$=new NStmtList(*$1, $2); $$->line=$1->line;}
    ;
Stmt:
    Exp SEMI {$$=new NExpStmt(*$1); $$->line=$2;}
    | CompSt {$$=new NCompStStmt(*$1); $$->line=$1->line;}      //复合语句结点直接最为语句结点，不再生成新的结点
    | RETURN Exp SEMI {$$=new NRetutnStmt(*$2); $$->line=$3;}
    | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=new NIfStmt(*$3, *$5); $$->line=$2;}
    | IF LP Exp RP Stmt ELSE Stmt {$$=new NIfElseStmt(*$3, *$5, *$7); $$->line=$2;}
    | WHILE LP Exp RP Stmt {$$=new NWhileStmt(*$3, *$5); $$->line=$2;}
    | BREAK SEMI {$$=new NBreakStmt(); $$->line=$2;}
    ;

/*Local Definitions*/
DefList: {$$=nullptr;}
    | Def DefList {$$=new NDefList(*$1, $2); $$->line=$1->line;}
    ;
Def:
    Specifier DecList SEMI {$$=new NDef(*$1, $2); $$->line=yylineno;}
    ;

DecList:
    Dec  {$$=new NDecList(*$1, nullptr); $$->line=yylineno;}
    | Dec COMMA DecList  {$$=new NDecList(*$1, $3); $$->line=yylineno;}
    ;
Dec:
    VarDec  {$$=new NDec(*$1); $$->line=yylineno;}
    | VarDec ASSIGNOP Exp  {$$=new NDec(*$1, $3); $$->line=yylineno;}
    ;

/*Expressions*/
Exp:
    Exp ASSIGNOP Exp {$$=new NAssignment(*(new std::string("ASSIGNOP")), *$1, $2, *$3); $$->line=yylineno;}//$$结点type_id空置未用，正好存放运算符
    | Exp PLUSASS Exp   {$$=new NAssignment(*(new std::string("PLUSASS")), *$1, $2, *$3); $$->line=yylineno;}//复合赋值运算
    | Exp MINUSASS Exp   {$$=new NAssignment(*(new std::string("MINUASS")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp STARASS Exp   {$$=new NAssignment(*(new std::string("STARASS")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp DIVASS Exp   {$$=new NAssignment(*(new std::string("DIVASS")), *$1, $2, *$3); $$->line=yylineno;}

    | PLUSPLUS Exp %prec UPLUSPLUS   {$$=new NSingleOperator(*(new std::string("PLUSPLUS")), $1, *$2); $$->line=yylineno;}//这里利用BISON %prec表示和UMINUS同优先级
    | MINUSMINUS Exp %prec UMINUSMINUS   {$$=new NSingleOperator(*(new std::string("MINUSMINUS")), $1, *$2); $$->line=yylineno;}//这里利用BISON %prec表示和UMINUS同优先级
    | Exp PLUSPLUS   {$$=new NSingleOperator(*(new std::string("PLUSPLUS")), $2, *$1); $$->line=yylineno;}//这里利用BISON %prec表示和UMINUS同优先级
    | Exp MINUSMINUS  {$$=new NSingleOperator(*(new std::string("MINUSMINUS")), $2, *$1); $$->line=yylineno;}//这里利用BISON %prec表示和UMINUS同优先级

    | Exp AND Exp   {$$=new NAssignment(*(new std::string("AND")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp OR Exp    {$$=new NAssignment(*(new std::string("OR")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp RELOP Exp {$$=new NAssignment(*(new std::string("RELOP")), *$1, RELOP, *$3); $$->line=yylineno;}  //词法分析关系运算符号自身值保存在$2中
    | Exp PLUS Exp  {$$=new NAssignment(*(new std::string("PLUS")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp MINUS Exp {$$=new NAssignment(*(new std::string("MINUS")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp STAR Exp  {$$=new NAssignment(*(new std::string("STAR")), *$1, $2, *$3); $$->line=yylineno;}
    | Exp DIV Exp   {$$=new NAssignment(*(new std::string("DIV")), *$1, $2, *$3); $$->line=yylineno;}
    
    | Exp MOD Exp   {$$=new NAssignment(*(new std::string("MOD")), *$1, $2, *$3); $$->line=yylineno;}
    
    | LP Exp RP     {$$=new NParenOperator(*$2); $$->line=yylineno;}
    | MINUS Exp %prec UMINUS   {$$=new NSingleOperator(*(new std::string("MINUS")), $1, *$2); $$->line=yylineno;}//这里利用BISON %prec表示和UMINUS同优先级 相当于虚拟出一个运算符
    | NOT Exp       {$$=new NSingleOperator(*(new std::string("NOT")), $1, *$2); $$->line=yylineno;}
    | ID LP Args RP {$$=new NMethodCall(*(new NIdentifier(*(new std::string($1)))), $3); $$->line=yylineno;}
    | ID LP RP      {$$=new NMethodCall(*(new NIdentifier(*(new std::string($1))))); $$->line=yylineno;}
    | Exp LB Exp RB {$$=new NListOperator(*$1, *$3); $$->line=yylineno;}
    | Exp DOT ID    {$$=new NDotOperator(*$1, *(new NIdentifier(*(new std::string($3))))); $$->line=yylineno;}
    | ID            {$$=new NIdentifier($1); $$->line=yylineno;}
    | INT           {$$=new NInteger($1); $$->line=yylineno;}
    | FLOAT         {$$=new NFloat($1); $$->line=yylineno;}
    | CHAR          {$$=new NChar($1); $$->line=yylineno;}
    ;
Args:
    Exp COMMA Args {$$=new NArgs(*$1, $3); $$->line=yylineno;}
    | Exp {$$=new NArgs(*$1, nullptr); $$->line=yylineno;}
    ;

%%


#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;//取参数对应的函数
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr,"%s",myerror);
    fprintf(stderr,"%s", ".\n");
    memset(myerror,0,sizeof(myerror));
}	
void myyyerror()
{
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    fprintf(stderr,"%s",myerror);
    fprintf(stderr, "%s",".\n");
    memset(myerror,0,sizeof(myerror));
}