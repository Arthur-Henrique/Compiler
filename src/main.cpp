#include "model.hpp"

extern int yyparse();

using namespace model;


int main(int argc, char **argv){
    yyparse();

    cout << " --- Compilation ends --- " << endl;


    delete WAREHOUSE;
    delete PROCESSOR;
}

