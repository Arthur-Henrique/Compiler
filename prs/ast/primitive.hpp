#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace ast {

	class Primitive : public Node{
	public:
		void* value;

		Primitive(void* _value) : value(_value){}

		virtual ~Primitive(){
			delete value;
		}

		template <typename T>
		T execute(){
			T* _value = (T*) value;
			return *_value;
		}
	};

	#define PRIMITIVE(NAME, TYPE) \
		class NAME : public Primitive{ \
		public: \
			NAME(TYPE _value) : Primitive(new TYPE(_value)){} \
			void print(){ \
				cout << execute<TYPE>(); \
				cout << "\t\tPrimitive" << endl; \
			} \
		};

	PRIMITIVE(Numeral, double)
	PRIMITIVE(Quote, string)
	PRIMITIVE(Booleaner, bool)

}
