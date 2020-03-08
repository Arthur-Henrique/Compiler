#pragma once

#include <map>
#include <utility>
#include <list>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
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
				define(id, false);
				return get(id);
			}
		}

		void define(string id, bool synchronize){
			Variable* defined = synchronize ? new SyncVariable(id) : new Variable(id);
			stock.insert(Element(id, defined));
		}

		void print(){
			printf("\n ~~~~~ WAREHOUSE ~~~~~ \n");
			Map::iterator it;
			for (it = stock.begin(); it != stock.end(); it++) {
				it->second->print();
			}
			printf(" ~~~~~~~~~~~~~~~~~~~~~~ \n");
		}
	};

	static Warehouse* WAREHOUSE;

	// ------------------------------------

	typedef list<Block*> Processes;
	typedef list<thread*> Threads;

	static void run(Block* instructions, shared_mutex* mtx, condition_variable_any* pause, int* finished){
		shared_lock<shared_mutex> hold(*mtx);
		pause->wait(hold, [&](){
			return *finished > 0;
		});

		printf("   -- Thread %d starts -- \n", instructions->id);
		instructions->execute();
		printf("   --- Thread %d ends --- \n", instructions->id);

		(*finished)++;
		pause->notify_all();
	}

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

			shared_mutex shr;
			condition_variable_any pause;

			int finished = 0;
			shr.lock();

			Processes::iterator it_p;
			for (it_p = processes.begin(); it_p != processes.end(); it_p++) {
				threads.push_back(new thread(model::run, *it_p, &shr, &pause, &finished));
			}

			this_thread::sleep_for(chrono::seconds(1));
			finished++;

			printf(" ~~~~~ Execution starts ~~~~~ \n");
			shr.unlock();
			pause.notify_all();

			mutex mtx;
			unique_lock<mutex> hold(mtx);

			pause.wait(hold, [&](){
				return finished == threads.size();
			});

			Threads::iterator it_t;
			for (it_t = threads.begin(); it_t != threads.end(); it_t++) {
				( *it_t )->join();
				pause.notify_all();
			}

			printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
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
