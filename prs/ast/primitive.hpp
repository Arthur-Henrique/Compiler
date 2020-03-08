#pragma once
#include <string>
#include <sstream>
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
			virtual string str(){ \
				ostringstream s; \
				s << execute<TYPE>(); \
				s << "\t\tPrimitive" << endl; \
				return s.str(); \
			} \
		};

	PRIMITIVE(Numeral, double)
	PRIMITIVE(Quote, string)
	PRIMITIVE(Booleaner, bool)

}
