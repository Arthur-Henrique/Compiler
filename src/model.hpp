#pragma once

#include <map>
#include <utility>
#include <list>
#include <string>
#include <thread>
#include <iostream>
#include "../prs/ast.h"

using namespace std;
using namespace ast;

namespace model{

	typedef map<string, Variable*> Map;
	typedef pair<string, Variable*> Element;

	static Map stock;

	class Warehouse {
	public:
		Warehouse(){ }

		Variable* get(string id){
			Map::iterator it = stock.find(id);
			if (it != stock.end()){
				return (*it).second;
			}
			else {
				Variable* defined = new Variable(id, NULL);
				stock.insert(Element(id, defined));
				return get(id);
			}
		}
	};

	static Warehouse* WAREHOUSE;

	// ------------------------------------

	typedef list<Block*> Processes;
	typedef list<thread*> Threads;

	static Processes processes;

	class Processor{
	public:

		Processor(){}

		~Processor(){
			Processes::iterator it;
			for (it = processes.begin(); it != processes.end(); it++) {
				delete *it;
			}
		}

		void compute(Block* instructions){
			processes.push_back(instructions);
		}

		void launch(){
			Threads threads;

			Processes::iterator it_p;
			for (it_p = processes.begin(); it_p != processes.end(); it_p++) {
				threads.push_back(new thread([](Block* instructions) -> void {
					cout << " ------- ";
					cout << "Thread " << instructions->id;
					cout << " ------- " << endl;
					instructions->execute();
				}, ( *it_p )));
			}

			Threads::iterator it_t;
			for (it_t = threads.begin(); it_t != threads.end(); it_t++) {
				( *it_t )->join();
			}
		}

		void print(){
			Processes::iterator it;
			for (it = processes.begin(); it != processes.end(); it++) {
				cout << endl;
				( *it )->print();
			}
		}
	};

	static Processor* PROCESSOR;



}
