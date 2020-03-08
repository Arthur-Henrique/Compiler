#pragma once
#include <time.h>
#include <iostream>

using namespace std;

namespace ast{

	class Delay : public Node{
	public:
		int seconds;

		Delay(double _seconds) : seconds(_seconds){}

		void execute(){
			this_thread::sleep_for(chrono::seconds(seconds));
		}

		virtual string str(){
			ostringstream s;
			s << "waiting " << seconds << "s";
			return s.str();
		}
	};

}