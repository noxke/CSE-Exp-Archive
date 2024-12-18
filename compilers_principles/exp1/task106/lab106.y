%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int yylex(void);
void yyerror(char const *);
%}


%define api.value.type {double}
/* Tokens */
%token NUM
%token EOL
%token ADD SUB MUL DIV

%% 
  /* Grammar rules and actions follow.  */
calclist:
	%empty
	|calclist exp EOL {printf("=%.10g\n",$2);}
	;

exp:
	term
	|exp ADD term {$$=$1+$3;}
	|exp SUB term {$$=$1-$3;}
	;

term:
	NUM
	|term MUL NUM {$$=$1*$3;}
	|term DIV NUM {$$=$1/$3;}
	;

%%

/* The lexical analyzer returns a double floating point
	number on the stack and the token NUM, or the numeric code
	of the character read if not a number.  It skips all blanks
	and tabs, and returns 0 for end-of-input.  */

/* begin */
int yylex(void)
{
	int c;
	while((c=getchar())==' '||c=='\t')
	continue;
	if(c=='.'||isdigit(c))
	{
	ungetc(c,stdin);
	if(scanf("%lf",&yylval)!=1)
		abort();
	return NUM;
	}
	switch(c){
	case EOF: return YYEOF;
	case '\n':return EOL;
	case '+': return ADD;
    case '-': return SUB;
	case '*': return MUL;
	case '/': return DIV;
	default:
		return c;
		
	}
	
}
/* end */

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