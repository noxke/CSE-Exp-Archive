#include "def.h"

#include "parser.hpp"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern "C"{
extern int yylex(void);
}
int allerror;

int yycolumn = 1;
int spaces = 0;
int main(int argc, char *argv[]) {
  yyin = fopen(argv[1], "r");
  if (!yyin)
    return 1;
  yylineno = 1;
  allerror = 0;

	//yylex();

  yyparse();
  // if (p) {
  //   p->parse();

  //   //Init
  //   InitializeModuleAndPassManager();
  //   p->codegen();
  // }
  return 0;
}