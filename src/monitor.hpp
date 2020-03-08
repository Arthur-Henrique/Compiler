#pragma once
#include <iostream>
#include <sstream>
#include <shared_mutex>
#include <sys/time.h>
#include <thread>
#include "logger.hpp"
#include "util.hpp"

namespace model{

	class Monitor{
	public:
		shared_mutex* mtx;
		timeval runtime;

		Monitor(shared_mutex* _mtx) : mtx(_mtx){
			gettimeofday(&runtime, NULL);
		}

		virtual string type() = 0;

		timeval blocked_interval(){
			timeval blocked_interval;
			timeval now;

			gettimeofday(&now, NULL);
			timersub(&now, &runtime, &blocked_interval);

			return blocked_interval;
		}

		void log_time(string identifier){
			ostringstream output;
			output << type() << identifier << " :: ";
			output << time_str(&runtime);

			timeval d = blocked_interval();
			if(d.tv_sec > 0 || d.tv_usec > 0.1) {
				output << " | " << duration_str(blocked_interval());
			}

			LOGGER.log(output.str());
		}
	};

	class Writer : public Monitor {
	public:
		Writer(shared_mutex* _mtx) : Monitor(_mtx) {
	    	mtx->lock();
		}

		~Writer(){
	    	mtx->unlock();
		}

		string type(){
			return "Writer ";
		}
	};

	class Reader : public Monitor {
	public:

		Reader(shared_mutex* _mtx) : Monitor(_mtx) {
	    	mtx->lock_shared();
		}

		~Reader(){
	    	mtx->unlock_shared();
		}

		string type(){
			return "Reader ";
		}
	};
}