#pragma once
#include <string>
#include <fstream>
#include <sys/time.h>

namespace model{

	static bool PRINT_LOG = true;

	class Logger{
	public:
		mutex mtx;

		void print(string text){
			mtx.lock();
			cout << text << endl;
			mtx.unlock();
		}

		void print(timeval moment){
			printf("%ld.%06ld\n", (long int) moment.tv_sec, (long int) moment.tv_usec);
		}

		string now(){
			time_t rawtime;
			struct tm *timeinfo;
			char buffer[80];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
			string str(buffer);

			return str;
		}

		void log(string text){
			mtx.lock();

			fstream log_file;
			log_file.open("tmp/log", ios::app);
			log_file << text << endl;
			log_file.close();

			mtx.unlock();

			if(PRINT_LOG)
				print(text);
		}
	};

	static Logger LOGGER;
}