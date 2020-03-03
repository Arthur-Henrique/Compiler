#pragma once
#include <iostream>

using namespace std;

namespace ast {

    class Assignment : public Node {
    public:
        Variable* variable;
        double value;

        Assignment(Variable* _variable, double _value)
        : variable(_variable), value(_value) {}

        void print(){
            cout << variable->id << " = " << value;
			cout << "\t\tAssignment" << endl;
		}

        void execute(){
        	variable->set(value);
//			print();
		}
    };

}