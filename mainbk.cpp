#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h> 
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <aws/lambda/LambdaClient.h>
#include <aws/lambda/model/InvokeRequest.h>
#include <aws/lambda/model/InvokeResult.h>
#include <aws/core/client/AWSError.h>
#include <aws/core/Core_EXPORTS.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/utils/UnreferencedParam.h>
#include <aws/core/client/AWSErrorMarshaller.h>

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
#include <time.h>
#include <chrono>

#include "json.hpp"
#define NANO_SECOND 1000000000

using namespace std;
using namespace std::chrono;
using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace Aws::Lambda;
using namespace Aws::Lambda::Model;
using namespace Aws::Utils;
using namespace Aws::Client;

static const char* KEY = "excameratempvideosample";
static const char* BUCKET = "excameratempvideos";

static pthread_mutex_t *lockarray;

class ExcameraRetryStrategy : public RetryStrategy {
    public:
	ExcameraRetryStrategy() {
	    m_maxRetries = 10;
    	}

	ExcameraRetryStrategy(long maxRetries, long scaleFactor) :
        		m_scaleFactor(0), m_maxRetries(10) {
	}

    	bool ShouldRetry(const AWSError<CoreErrors>& error, long attemptedRetries) const {
		if (attemptedRetries >= m_maxRetries) {
        		return false;
		}

    		return error.ShouldRetry();
    	}

	long CalculateDelayBeforeNextRetry(const AWSError<CoreErrors>& error, long attemptedRetries) const {
		return 0;
	}

    private:
    	long m_scaleFactor;
    	long m_maxRetries;
};

class LambdaInvocationRecord {
    public:
	LambdaInvocationRecord() {
	    start_time_inside = 0;
	    end_time_inside   = 0;
	    result            = false;
	    str               = "";
	}

    	high_resolution_clock::time_point start_time;
    	high_resolution_clock::time_point end_time;
	double start_time_inside;
	double end_time_inside;
	bool result;
	std::string str;
};

static high_resolution_clock::time_point getTime()
{
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  return std::chrono::time_point_cast<std::chrono::nanoseconds>(t1);
}

static double elapsed(high_resolution_clock::time_point t2, high_resolution_clock::time_point t1)
{
  return duration_cast<chrono::seconds>(t2 - t1).count();
}

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

void writeToFile(char* filename, int n, LambdaInvocationRecord lir) {
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

LambdaInvocationRecord lambda_invoke_request(Aws::Lambda::LambdaClient &client,
				  Aws::Lambda::Model::InvokeRequest &ir) {
    std::string str("");
    LambdaInvocationRecord lir;
    lir.start_time = getTime();
    auto invokeOutcome = client.Invoke(ir);
    if(invokeOutcome.IsSuccess()) {
        basic_streambuf<char>* buf = invokeOutcome.GetResult().GetPayload().rdbuf();
	lir.result = true;
	lir.str = str;
    	if (buf == NULL) {
            return lir;
        }
     	string sbuf = streambufToString(buf);
     	if (sbuf.empty()) {
            return lir;
     	}
	lir.str = sbuf;
	lir.end_time = getTime();
     	return lir;
    } else {
        lir.result = false;
	lir.str = str;
	return lir;
    }
    
}

int main(int argc, char* argv[])
{
    cout<<"Starting AWS Lambda Test\n";

    init_locks();

    if (argc < 4) {
	cout<<"Too few arguments."<<endl;
	return -1;
    }
    int nLambdas = atoi(argv[1]);
    char* functionName = argv[2];
    char* filename = argv[3];

    ofstream myfile;
    myfile.open(filename, ios::out);
    myfile.close();

    static const char* CLIENT_CONFIGURATION_ALLOCATION_TAG = "ClientConfiguration";
    Aws::Client::ClientConfiguration config;
    config.region = Aws::Region::EU_WEST_1;
    config.requestTimeoutMs = 10000;
    config.maxConnections = 1200;
    config.retryStrategy = Aws::MakeShared<ExcameraRetryStrategy>(CLIENT_CONFIGURATION_ALLOCATION_TAG);

    std::vector<std::future<LambdaInvocationRecord>> futures;
    Aws::Lambda::Model::InvokeRequest invokerequest;
    invokerequest.WithFunctionName(functionName);
    Aws::Lambda::LambdaClient client{config};

    vector<double> diff_times_lambda_only;
    vector<double> diff_times_lambda_network;
    high_resolution_clock::time_point beginTime, endTime;

    beginTime = getTime();
    for(int i = 0; i < nLambdas; i++) {
    	//futures.push_back(client.InvokeCallable(invokerequest));
	futures.push_back(std::async(std::launch::async, 
				     lambda_invoke_request,
				     std::ref(client),
				     std::ref(invokerequest)
				    )
			 );
    }

    int success = 0;
    int failures = 0;
    int i = 0;
    for(auto &e : futures){
	LambdaInvocationRecord lir = e.get();
	if (lir.result == true) {
	    success += 1;
	    auto json = nlohmann::json::parse(lir.str);
            string output = json.find("output").value();
	    double stt  = json.find("start_time").value();
	    double endt = json.find("end_time").value();
	    lir.start_time_inside = stt;
	    lir.end_time_inside   = endt;
	    diff_times_lambda_only.push_back(endt - stt);
            diff_times_lambda_network.push_back(elapsed(lir.end_time, lir.start_time));
	} else {
	    failures += 1;
	}
	writeToFile(filename, i, lir);
	i++;
    }

    endTime = getTime();
    cout<<"Total execution time of "<<nLambdas<<": "<<elapsed(endTime, beginTime)<<endl;

    init_locks();

    cout<<"Average time including network latency : "<<average(diff_times_lambda_network)<<endl;
    cout<<"Average time excluding network latency : "<<average(diff_times_lambda_only)<<endl;
    cout<<"Total no. of success : "<<success<<" and total no. of failures : "<<failures<<endl;

    return 0;  
}
