%{
#include "string.h"
#include "def.h"

extern int yycolumn;

#define YYSTYPE yylval
extern "C"
{	
	int yywrap(void);
	int yylex(void);
}

void flexout(std::string name,std::string value){
  std::cout<<name<<"\t:"<<value<<std::endl;
}
//flex为bison提供行号信息
%}
%option yylineno 

INT			   [\-]?[1-9][0-9]*|0
OCTINT       [\-]?0[1-7][0-7]*
HEXINT     [\-]?0x[1-9a-fA-F][0-9a-fA-F]*
FLOAT1     [\-]?[0-9]+\.[0-9]+
FLOAT2     [\-]?[0-9]+\.[0-9]+e[\-]?[1-9][0-9]*
IDENT			 [A-Za-z][A-Za-z0-9]*

%%

"int"        {flexout("TYPE", yytext);}
"float"      {flexout("TYPE", yytext);}
"char"       {flexout("TYPE", yytext);}
>|<|>=|<=|!=|==     {flexout("RELOP", yytext);}
";"          {flexout("SEMI", yytext);}
","          {flexout("COMMA", yytext);}
"="          {flexout("ASSIGNOP", yytext);}
"+"          {flexout("PLUS", yytext);}
"-"          {flexout("MINUS", yytext);}
"*"          {flexout("STAR", yytext);}
"/"          {flexout("DIV", yytext);}
"&&"         {flexout("AND", yytext);}
"||"         {flexout("OR", yytext);}
"."          {flexout("DOT", yytext);}
"!"          {flexout("NOT", yytext);}
"("          {flexout("LP", yytext);}
")"          {flexout("RP", yytext);}
"["          {flexout("LB", yytext);}
"]"          {flexout("RB", yytext);}
"{"          {flexout("LC", yytext);}
"}"          {flexout("RC", yytext);}
"++"         {flexout("PLUSPLUS", yytext);}
"--"         {flexout("MINUSMINUS", yytext);}
"+="         {flexout("PLUSASS", yytext);}
"-="         {flexout("MINUSASS", yytext);}
"struct"     {flexout("STRUCT", yytext);}
"return"     {flexout("RETURN", yytext);}
"if"         {flexout("IF", yytext);}
"else"       {flexout("ELSE", yytext);}
"while"      {flexout("WHILE", yytext);}

{IDENT}      {flexout("ID", yytext);}
{INT}        {flexout("INT", yytext);}
{OCTINT}     {flexout("INT", yytext);}
{HEXINT}     {flexout("INT", yytext);}
{FLOAT1}      {flexout("FLOAT", yytext);}
{FLOAT2}      {flexout("FLOAT", yytext);}

[\n]		     {yycolumn=1;}
[ \r\t]		   {/*printf("过滤空格等字符\n");*/}
0(([0,8,9][0-9]*)|([1-7]([0-7]*[8,9]+[0-7]*)+))                               {printf("Error type A at Line %d: Illegal octal number '%s'\n", yylineno, yytext);}
0x(([0,G-Zg-z][0-9A-Za-z]*)|([1-9A-Fa-f]([0-9A-Fa-f]*[G-Zg-z]+[0-9A-Fa-f]*)+))            {printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n", yylineno, yytext);}
.           {printf("Error type A at Line %d: Mysterious characters '%s'\n", yylineno, yytext);}
%%

int yywrap()
{
    return 1;
}