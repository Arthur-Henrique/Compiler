#pragma once
#include <iostream>

using namespace std;

namespace ast {

    class Log : public Node {
    public:
        Node* node;

        Log(Node* _node) : node(_node) {}

        void execute(){
        	node->print();
        }

		virtual string str(){
			ostringstream s;
			s << "log	" ;
			s << node->str();
			return s.str();
		}
	};

}