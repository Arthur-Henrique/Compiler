#pragma once
#include <iostream>
#include <string>
#include <sys/time.h>

using namespace std;

namespace model{

	static string time_str(timeval* moment){
//		time_t time = moment.tv_sec;
		tm* tm = localtime(&moment->tv_sec);
		char buf1[64], buf2[64];

		strftime(buf1, sizeof buf1, "%Y-%m-%d %H:%M:%S", tm);
		snprintf(buf2, sizeof buf2, "%s.%06ld", buf1, moment->tv_usec);

		return string(buf2);
	}

	static string duration_str(timeval duration){
		ostringstream stream;
		stream << (long int) duration.tv_sec << "." << (long int) duration.tv_usec;
		return stream.str();
	}

}