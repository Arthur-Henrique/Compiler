#pragma once

#include <list>
#include <iostream>

using namespace std;

namespace ast{

	typedef list<Node*> Instructions;

	static int _id = 0;

	class Block{
	public:
		int id;
		Instructions instructions = {};

		Block() : id(_id++){}

		~Block(){
			Instructions::iterator it;
			for (it = instructions.begin(); it != instructions.end(); it++) {
				delete *it;
			}
		}

		void insert(Node* instruction){
			instructions.push_back(instruction);
		}

		void execute(){
			 Instructions::iterator it;
			for (it = instructions.begin(); it != instructions.end(); it++) {
				(*it)->execute();
			}
		}

		void print(){
			cout << "Block {" << endl;
            Instructions::iterator it;
			for (it = instructions.begin(); it != instructions.end(); it++) {
				cout << "\t";
				( *it )->print();
			}
			cout << "}" << endl;
		}
	};
}
