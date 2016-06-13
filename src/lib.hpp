#ifndef LIB_H
#define LIB_H

#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

#include "LambdaInvocationRecord.hpp"

using namespace std;
using namespace std::chrono;

class LambdaInvocationRecord;

high_resolution_clock::time_point getTime();

double 
elapsed(high_resolution_clock::time_point t2,
	high_resolution_clock::time_point t1);

double
average(vector<double> times);

string
streambufToString(basic_streambuf<char>* buf);

double
convertClockToDouble(high_resolution_clock::time_point t);

void
writeToFile(char* filename,
	    int n,
	    LambdaInvocationRecord lir);

#endif
