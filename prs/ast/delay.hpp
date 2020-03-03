#pragma once
#include <time.h>
#include <iostream>

using namespace std;

namespace ast{

	class Delay : public Node{
	public:
		int seconds;

		Delay(double _seconds) : seconds(_seconds){}

		void print(){
			cout << "wait " << seconds << "s";
		}

		void execute(){
			chrono::milliseconds timespan(seconds);
			this_thread::sleep_for(timespan);
		}
	};

}