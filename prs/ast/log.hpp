#pragma once
#include <iostream>

using namespace std;

namespace ast {

    class Log : public Node {
    public:
        Node* node;

        Log(Node* _node) : node(_node) {}

        void print(){
            cout << "log	" ;
			node->print();
        }

        void execute(){
        	node->print();
        }
    };

}