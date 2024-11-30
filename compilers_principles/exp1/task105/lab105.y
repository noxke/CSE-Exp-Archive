%{
  #include <ctype.h> /*需要使用的头文件*/
  #include <stdio.h>
  #include <math.h>
  int yylex (void);  /*需要使用的词法分析函数的声明*/
  void yyerror (char const *);
%}
%token NUM     /*需要的终结符声明*/
%define api.value.type {double}
%left '+' '-'   /*结合性、优先级*/
%left '*' '/'
%right 'n'
%right '^'
%% 
/* Grammar rules and actions follow.  */
input:
    %empty
    | input line
    ;
line:
    '\n'
    | exp '\n'      { printf ("%.10g\n", $1); }
    ;
exp:
  NUM    {$$=$1;}   /*NUM NUM +*/
  |exp 'n' {$$=-$1;}
  |exp exp '+' {$$=$1+$2;}      
  |exp exp '-' {$$=$1-$2;}
  |exp exp '/' {$$=$1/$2;}      
  |exp exp '*' {$$=$1*$2;}
  |exp exp '^' {$$=pow($1,$2);}
  ;
%%
/* The lexical analyzer returns a double floating point
number on the stack and the token NUM, or the numeric code
of the character read if not a number.  It skips all blanks and tabs, and returns 0 for end-of-input.  */
int yylex (void)
{
  int c;
  /* Skip white space.  */
  while ((c = getchar ()) == ' ' || c == '\t')
    continue;
  /* Process numbers.  */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      scanf ("%lf", &yylval);
      return NUM;
    }
  /* Return end-of-input.  */
  if (c == EOF)
    return 0;
  if (c == '!')
      return 0;
  /* Return a single char.  */
  return c;
}
int main (int argc, char** argv)
{
  yyparse();
  return 0;
}
/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}