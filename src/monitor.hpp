#pragma once
#include <string>
#include <iostream>
#include <shared_mutex>
#include <time.h>
#include <thread>

namespace model {
	class Monitor{
	public:
		shared_mutex* mtx;
		time_t runtime;

		Monitor(shared_mutex* _mtx) : mtx(_mtx), runtime(time(NULL)) {}
	};

	class Writer : public Monitor {
	public:
		Writer(shared_mutex* _mtx) : Monitor(_mtx){
			mtx->lock();
		}

		virtual ~Writer(){
	    	mtx->unlock();
		}
	};

	class Reader : public Monitor {
	public:
		Reader(shared_mutex* _mtx) : Monitor(_mtx){
			mtx->lock_shared();
		}

		virtual ~Reader(){
	    	mtx->unlock_shared();
		}
	};

}

//	struct Proxy {
//	public:
//		shared_mutex* mtx;
//		string id;
//		double* value;
//		time_t runtime;
//
//		Proxy(mutex* _mtx, condition_variable* _busy, double* _value, string _id)
//		: mtx(_mtx), value(_value), busy(_busy), id(_id), runtime(time(NULL)) {
///**/    	mtx->lock();
//		}
//
//		double get(){
//			cout << id << ".get() :: " << ctime(&runtime) << endl;
//			return *value;
//		}
//
//		void set(double _value){
//			cout << id << ".set(" << _value << ") :: " << ctime(&runtime) << endl;
//			*value = _value;
//
//			chrono::milliseconds timespan(1000);
//			this_thread::sleep_for(timespan);
//		}
//
//		~Proxy(){
///**/    	mtx->unlock();
//		}
//	};
