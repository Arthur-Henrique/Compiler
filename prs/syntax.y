%code requires{
	#define YY_NO_UNPUT

	#include <iostream>
	#include <stdio.h>
	#include <string>

	#include "ast.h"
	#include "../src/model.hpp"

	using namespace std;
	using namespace ast;
	using namespace model;

	extern void log(string s);
	extern int yyerror(char *s);
	extern int yylex(void);
}

%initial-action{
	log("FEDERAL UNIVERSITY OF SANTA CATARINA");
	log("INE5424 - Operational System II");
	log("Arthur Henrique Della Fraga");
	log("\nThread-safe compiler\n");

	log(" ~~~~~ Compilation starts ~~~~~");
};

%union{
	Node* node;
	Block* block;

	Primitive* primitive;
	Variable* variable;
	Assignment* assignment;

	string* id;
}

%start compile

%type <node> program
%type <node> synchronize
%type <node> line

%type <variable> variable
%type <assignment> assignment

%type <block> block

%token <primitive> NUMBER
%token <primitive> TEXT
%token <primitive> BOOLEAN
%token <id> ID

%left ';' '{' '}' '=' '%' '$'
%right '~'

%%

compile     : program {
				log(" ~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

//				PROCESSOR->print();
				PROCESSOR->launch();
				WAREHOUSE->print();
			}

program     : '{' block '}' {
				PROCESSOR->compute($2);
			}
			| program '{' block '}' {
				PROCESSOR->compute($3);
			}
			| program ';'
			| synchronize

synchronize : '~' ID{
				WAREHOUSE->define(*$2, true);
			}
			| synchronize ',' ID {
				WAREHOUSE->define(*$3, true);
			}

block       : line ';' {
				$$ = new Block();
				$$->insert($1);
			}
			| block line ';' {
				$1->insert($2);
			}

line        : NUMBER { $$ = $1; log("number"); }
			| BOOLEAN { $$ = $1; log("boolean"); }
			| TEXT { $$ = $1; log("text"); }
	        | variable { $$ = $1; log("variable"); }
	        | assignment { $$ = $1; log("assignment"); }
	        | '$' NUMBER { $$ = new Delay($2->execute<double>()); log("delay"); }

variable    : ID {
				$$ = WAREHOUSE->get(*$1);
            }
            | '!' ID {
                $$ = WAREHOUSE->get(*$2);
            }

assignment  : variable '=' NUMBER {
				$$ = new Assignment($1, $3->execute<double>());
			}

%%

void log(string s){
	cout << s << endl;
}

int yyerror(string s){
	extern int yylineno;	// defined and maintained in lex.c
	extern char *yytext;	// defined and maintained in lex.c

	cerr << "ERROR: " << s << " at symbol \"" << yytext;
	cerr << "\" on line " << yylineno << endl;
	exit(1);
}

int yyerror(char *s){
	return yyerror(string(s));
}
