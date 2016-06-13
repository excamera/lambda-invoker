#include <iostream>
#include <fstream>

#include "lib.hpp"
#include "LambdaInvocationRecord.hpp"

using namespace std;

class LambdaInvocationRecord;

static high_resolution_clock::time_point getTime()
{
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  return std::chrono::time_point_cast<std::chrono::nanoseconds>(t1);
}

static double elapsed(high_resolution_clock::time_point t2, high_resolution_clock::time_point t1)
{
  return duration_cast<chrono::seconds>(t2 - t1).count();
}

double average(vector<double> times) {
  double avg = 0;
  int size = times.size();
  for(vector<double>::iterator it = times.begin() ; it != times.end(); ++it) {
    avg += *it;
  }
  return avg/(double)size;
}

string streambufToString(basic_streambuf<char>* buf) {
  string s = "";
  if (buf == NULL) {
    return s;
  }

  do {
    char ch = buf->sgetc();
    s += ch;
  } while(buf->snextc() != streambuf::traits_type::eof());
  return s;
}

double convertClockToDouble(high_resolution_clock::time_point t)
{
  unsigned long ul = t.time_since_epoch() / std::chrono::milliseconds(1);
  double d = (double)ul / 1000;
  return d;
}

void writeToFile(char* filename, int n, LambdaInvocationRecord lir)
{
  ofstream myfile;
  myfile.open(filename,  ios::out | ios::app);
  myfile<<std::fixed
        <<n
        <<","
        <<convertClockToDouble(lir.start_time)
        <<","
        <<lir.start_time_inside
        <<","
        <<lir.end_time_inside
        <<","
        <<convertClockToDouble(lir.end_time)
        <<"\n";
  myfile.close();
}
