#pragma once
#include <string>

using namespace std;

namespace ast{

	class Node{
	public:
		virtual ~Node(){}

		virtual void execute(){
//        	print();
		}

		virtual void print(){
			cout << str();
		}

		virtual string str() = 0;
	};

}