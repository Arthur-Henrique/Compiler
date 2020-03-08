#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <shared_mutex>
#include "../../src/monitor.hpp"


using namespace std;
using namespace model;

namespace ast {

	class Variable : public Node {
	public:
		string id;
        double value;

        Variable(string _id) : id(_id), value(NULL) {}
        Variable(string _id, double _value) : id(_id), value(_value) {}

        ~Variable(){}

        virtual double get(){
        	return value;
        }

        virtual void set(double _value){
			value = _value;
		}

		virtual void execute(){
        	get();
        }

        virtual string str(){
        	ostringstream s;
            s << id << " : " << value;
			s << "\t\tVariable" << endl;
			return s.str();
		}
	};


    class SyncVariable : public Variable {
    public:
        shared_mutex mtx;

        SyncVariable(string _id) : Variable(_id) {}
        SyncVariable(string _id, double _value) : Variable(_id, _value) {}

        ~SyncVariable(){}

        double get(){
        	return R(&mtx, &value, id).get();
        }

		void set(double _value){
			W(&mtx, &value, id).set(_value);
		}

		string str(){
        	ostringstream s;
            s << id << " : " << value;
			s << "\t\tSyncVariable" << endl;
			return 	s.str();
		}

		class R : public Reader {
		public:
			string id;
			double* value;

			R(shared_mutex* _mtx, double* _value, string _id)
			: Reader(_mtx), value(_value), id(_id) {}

			double get(){
				log_time(id);
				return *value;
			}

			~R(){}
		};

        class W : public Writer {
		public:
			string id;
			double* value;

			W(shared_mutex* _mtx, double* _value, string _id)
			: Writer(_mtx), value(_value), id(_id) {}

			void set(double _value){
				log_time(id);

				this_thread::sleep_for(chrono::seconds(1));

				*value = _value;
			}

			~W(){}
		};
    };

}