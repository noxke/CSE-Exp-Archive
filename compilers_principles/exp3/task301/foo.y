 //这个例子中有一些问题，请调试修改
%union
{
	int ival;
	const char *sval;
}
%token <ival>NUM
%nterm <ival>exp
%left '-'
%left '+'
%%
exp:
    exp '+' exp
	|exp '-' exp
    |NUM
	;
%% //**end**//