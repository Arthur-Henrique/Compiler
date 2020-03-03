#pragma once

using namespace std;

namespace ast {

	class Node{
	public:
		virtual ~Node(){}

		virtual void execute(){
//        	print();
        }

		virtual void print() = 0;
	};

}
