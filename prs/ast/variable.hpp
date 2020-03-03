#pragma once
#include <string>
#include <iostream>
#include <shared_mutex>
#include "../../src/monitor.hpp"

using namespace std;
using namespace model;

namespace ast {

	class Variable : public Node {
    public:
		shared_mutex mtx;
		string id;
		double value;

        Variable(string _id) : id(_id), value(NULL) {}
        Variable(string _id, double _value) : id(_id), value(_value) {}

        ~Variable(){}

        void execute(){
        	get();
        }

        void print(){
            cout << id << " : " << value;
			cout << "\t\tVariable" << endl;
		}

        double get(){
        	cout << id << " " << &mtx << endl;
        	return R(&mtx, &value, id).get();
        }

		void set(double _value){
        	cout << id << " " << &mtx << endl;

			W(&mtx, &value, id).set(_value);
		}

        class W : public Writer {
        public:
        	string id;
        	double* value;

        	W(shared_mutex* _mtx, double* _value, string _id)
        	: Writer(mtx), id(_id), value(_value) {}

        	void set(double _value){
        		cout << id << ".set(" << _value << ") :: " << ctime(&runtime);
				*value = _value;
			}

			~W(){}
        };

        class R : public Reader {
        public:
        	string id;
        	double* value;

        	R(shared_mutex* _mtx, double* _value, string _id)
        	: Reader(mtx), id(_id), value(_value) {}

        	double get(){
        		cout << id << ".get() :: " << ctime(&runtime);
				return *value;
			}

			~R(){}
        };
    };

}