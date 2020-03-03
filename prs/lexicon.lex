%{
	#define YY_NO_UNPUT

	#include "syntax.h"

	using namespace std;

	extern int yyerror(char *s);
%}

%option noyywrap nodefault yylineno

number  {digit}+(\.{digit}+)?
text    \"([^\"\\\\]|\\\\.)*\"

word    ({letter}+[.-_]?)+

digit	[0-9]
letter  [a-zA-Z]

%%

{number}                { yylval.primitive = new Numeral(atof(yytext)); return NUMBER; }
{text}                  {
							string quote = strdup(yytext);

							yylval.primitive = new Quote(quote);
							return TEXT;
						}

[tT][rR][uU][eE]        { yylval.primitive = new Booleaner(true); return BOOLEAN; }
[fF][aA][lL][sS][eE]    { yylval.primitive = new Booleaner(false); return BOOLEAN; }

{word}                  { yylval.id = new string(strdup(yytext)); return ID; }

"="                     { return '='; }
"{"(\n)*                { return '{'; }
"}"                     { return '}'; }
"$"                     { return '$'; }
"%%"                    { return '%'; }



[ \t]*		            {}
[;\n]*                  { return ';'; }


.		                { yyerror(strdup(yytext)); exit(1); }

%%
