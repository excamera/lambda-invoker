#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h> 
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <aws/lambda/LambdaClient.h>
#include <aws/lambda/model/InvokeRequest.h>

#include <fstream>
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>

#include "json.hpp"

using namespace std;
using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace Aws::Lambda;
using namespace Aws::Lambda::Model;

static const char* KEY = "excameratempvideosample";
static const char* BUCKET = "excameratempvideos";

static pthread_mutex_t *lockarray;

class LambdaInvoke {
    public:
	LambdaInvoke() {
	    
	}

	LambdaInvoke(int num, double s, double e) {
	    n = num;
	    start_time = s;
	    end_time = e;
	}

	int n;
    	double start_time;
    	double end_time;
};

static void lock_callback(int mode, int type, char *file, int line)
{
  (void)file;
  (void)line;
  if (mode & CRYPTO_LOCK) {
    pthread_mutex_lock(&(lockarray[type]));
  }
  else {
    pthread_mutex_unlock(&(lockarray[type]));
  }
}

static unsigned long thread_id(void)
{
  unsigned long ret;

  ret=(unsigned long)pthread_self();
  return(ret);
}

static void init_locks(void)
{
  int i;

  lockarray=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
                                        sizeof(pthread_mutex_t));
  for (i=0; i<CRYPTO_num_locks(); i++) {
    pthread_mutex_init(&(lockarray[i]),NULL);
  }

  CRYPTO_set_id_callback((unsigned long (*)())thread_id);
  CRYPTO_set_locking_callback((void (*)(int, int, const char*, int))lock_callback);
}

static void kill_locks(void)
{
  int i;

  CRYPTO_set_locking_callback(NULL);
  for (i=0; i<CRYPTO_num_locks(); i++)
    pthread_mutex_destroy(&(lockarray[i]));

  OPENSSL_free(lockarray);
}

clock_t begin() {
    return clock();
}

clock_t end() {
    return clock();
}

double elapsed(clock_t begin, clock_t end) {
    return ((double) (end - begin)) / CLOCKS_PER_SEC;
}

double toTime(clock_t t) {
    return ((double) t) / CLOCKS_PER_SEC;
}

double average(vector<double> times) {
    double avg = 0;
    int size = times.size();
    for(vector<double>::iterator it = times.begin() ; it != times.end(); ++it) {
    	avg += *it;
    }
    return avg/size;
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

void writeToFile(vector<LambdaInvoke> a) {
    ofstream myfile;
    myfile.open ("results.txt");
    for(vector<LambdaInvoke>::iterator it = a.begin(); it != a.end(); ++it) {
	LambdaInvoke li = *it;
	myfile<<li.n<<","<<li.start_time<<","<<li.end_time<<"\n";
    }
    myfile.close();
}

int main(int argc, char* argv[])
{
    cout<<"Starting AWS Lambda Test\n";
    init_locks();
    int nLambdas = atoi(argv[1]);
    Aws::Client::ClientConfiguration config;
    config.region = Aws::Region::EU_WEST_1;
    config.requestTimeoutMs = 10000;
    config.maxConnections = 1100;

    vector<Aws::Lambda::Model::InvokeOutcomeCallable> futures;
    vector<LambdaInvoke> livector;
    Aws::Lambda::Model::InvokeRequest invokerequest;
    invokerequest.WithFunctionName("testLamba");
    Aws::Lambda::LambdaClient client{config};

    vector<double> start_times;
    vector<double> end_times;
    vector<double> diff_times;
    double start_time_network[nLambdas];
    double diff_time_network = 0;
    int i;

    clock_t beginTime = begin();
    for(i = 0; i < nLambdas; i++) {
	start_time_network[i] = begin();
    	futures.push_back(client.InvokeCallable(invokerequest));
	
    }
    int success = 0;
    int failures = 0;
    i = 0;
    for(auto &e : futures){
	auto invokeOutcome = e.get();
    	if(invokeOutcome.IsSuccess()){
	    success += 1;
	    basic_streambuf<char>* buf = invokeOutcome.GetResult().GetPayload().rdbuf();
	    if (buf == NULL) {
		cout<<"Check Lambda Function Name. InvokeOutcome is NULL\n";
		return -1;
	    }
	    string sbuf = streambufToString(buf);
	    if (sbuf.empty()) {
		cout<<"Conversion from streambuf to buf failed\n";
		return -1;
	    }
	    auto json = nlohmann::json::parse(sbuf);
            string output = json.find("output").value();
	    double stt  = json.find("start_time").value();
	    double endt = json.find("end_time").value();
            //start_times.push_back(stt);
            //end_times.push_back(endt);
	    diff_times.push_back(endt-stt);
	    clock_t end_time_network = end();
	    diff_time_network += elapsed(start_time_network[i], end_time_network);
	    LambdaInvoke li(i, toTime(start_time_network[i]), toTime(end_time_network));
            livector.push_back(li);
	    i++;
    	} else {
	    failures += 1;
	    cout<<"Error while putting Object "<<invokeOutcome.GetError().GetExceptionName()<<" "<<invokeOutcome.GetError().GetMessage()<<endl;
 	}
    }

    clock_t endTime = end();
    cout<<"Total execution time of "<<nLambdas<<": "<<elapsed(beginTime, endTime)<<endl;

    init_locks();

    writeToFile(livector);
    cout<<"Average time including network latency : "<<diff_time_network/success<<endl;
    cout<<"Average time excluding network latency : "<<average(diff_times)<<endl;
    cout<<"Total no. of success : "<<success<<" and total no. of failures : "<<failures<<endl;

    return 0;  
}
