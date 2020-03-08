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

        void execute(){
        	variable->set(value);
//			print();
		}

		virtual string str(){
			ostringstream s;
			s << variable->id << " = " << value;
			s << "\t\tAssignment" << endl;
			return s.str();
		}
	};

}