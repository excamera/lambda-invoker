// Add the AWS header files here
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
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/core/utils/UnreferencedParam.h>
#include <aws/core/client/AWSErrorMarshaller.h>

// Add C++ header files here
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
#include <unistd.h>

// Add Third party header files here
#include "json.hpp"

// Add project related header files here
#include "lib.hpp"
#include "ExcameraRetryStrategy.hpp"
#include "LambdaInvocationRecord.hpp"

// Define constants here
#define NANO_SECOND 1000000000

// Declare C++ namespaces here
using namespace std;
using namespace std::chrono;

// Declare AWS namespaces here
using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace Aws::Lambda;
using namespace Aws::Lambda::Model;
using namespace Aws::Utils;
using namespace Aws::Client;

// Define static constants here
static const char* KEY = "excameratempvideosample";
static const char* BUCKET = "excameratempvideos";
static pthread_mutex_t *lockarray;

// Functions start from here
static void 
lock_callback(int mode, int type, char *file, int line)
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

static unsigned long 
thread_id(void)
{
  unsigned long ret;

  ret=(unsigned long)pthread_self();
  return(ret);
}

static void 
init_locks(void)
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

static void 
kill_locks(void)
{
  int i;

  CRYPTO_set_locking_callback(NULL);
  for (i=0; i<CRYPTO_num_locks(); i++)
    pthread_mutex_destroy(&(lockarray[i]));

  OPENSSL_free(lockarray);
}

LambdaInvocationRecord
lambda_invoke_request(Aws::Lambda::LambdaClient &client,
		      Aws::Lambda::Model::InvokeRequest &ir)
{
  std::string str("");
  LambdaInvocationRecord lir;
  lir.start_time = getTime();
  auto invokeOutcome = client.Invoke(ir);
  if(invokeOutcome.IsSuccess()) {
    basic_streambuf<char>* buf = invokeOutcome.GetResult().GetPayload().rdbuf();
    lir.result 		       = true;
    lir.str    		       = str;
    if (buf == NULL) {
      return lir;
    }
    string sbuf = streambufToString(buf);
    if (sbuf.empty()) {
      return lir;
    }
    lir.str      = sbuf;
    lir.end_time = getTime();
    return lir;
  } else {
    lir.result 	    = false;
    lir.str 	    = str;
    lir.aws_error   = invokeOutcome.GetError();
    
    Aws::Client::AWSError<Aws::Lambda::LambdaErrors> aws_error = lir.aws_error;
    Aws::Lambda::LambdaErrors errCode = aws_error.GetErrorType();
    switch (errCode)
    {
      case Aws::Lambda::LambdaErrors::TOO_MANY_REQUESTS:
	std::cout << "Retrying from script..." << std::endl;
	//return lambda_invoke_request(client, ir);
	break;
      default:
        break;
    }
    return lir;
  }
}

int 
main(int argc, char* argv[])
{
    cout<<"Starting AWS Lambda Test\n";

    init_locks();

    if (argc < 4) {
	cout<<"Too few arguments."<<endl;
	return -1;
    }
    int nLambdas       = atoi(argv[1]);
    char* functionName = argv[2];
    char* filename     = argv[3];
    long maxRetries    = 0;
    long scaleFactor   = 0;

    if (argc >= 5) {
	maxRetries = atol(argv[4]);	
    } else {
	maxRetries = 10;
    }

    if (argc >= 6) {
	scaleFactor = atol(argv[5]);
    } else {
	scaleFactor = 25;
    }

    std::cout << "nLambdas : "    << nLambdas   << " lambda : "           << functionName << std::endl;
    std::cout << "Retry count : " << maxRetries << " and Scale Factor : " << scaleFactor  << std::endl;

    ofstream myfile;
    myfile.open(filename, ios::out);
    myfile.close();

    static const char* CLIENT_CONFIGURATION_ALLOCATION_TAG = "ClientConfiguration";
    Aws::Client::ClientConfiguration config;
    config.region           = Aws::Region::EU_WEST_1;
    config.requestTimeoutMs = 30000;
    config.connectTimeoutMs = 30000;
    config.maxConnections   = 1200;
    config.retryStrategy    = Aws::MakeShared<DefaultRetryStrategy>(CLIENT_CONFIGURATION_ALLOCATION_TAG, maxRetries, scaleFactor);

    std::vector<std::future<LambdaInvocationRecord>> futures;
    Aws::Lambda::Model::InvokeRequest invokerequest;
    invokerequest.WithFunctionName(functionName);
    Aws::Lambda::LambdaClient client{config};

    vector<double> diff_times_lambda_only;
    vector<double> diff_times_lambda_network;
    high_resolution_clock::time_point beginTime, endTime;

    beginTime = getTime();
    for(int i = 0; i < nLambdas; i++) {
	/* Original method
	 * [futures.push_back(client.InvokeCallable(invokerequest));]
	 * is to push InvokeCallable and
	 * get InvokeCallableOutCome. Since we need the invokeOutcome
	 * details through LIR object in the caller, we have changed
	 * the way we push into future and get it back
	 */
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
	    Aws::Client::AWSError<Aws::Lambda::LambdaErrors> aws_error = lir.aws_error;
	    Aws::Lambda::LambdaErrors errCode = aws_error.GetErrorType();
	    switch (errCode)
            {
                case Aws::Lambda::LambdaErrors::RESOURCE_NOT_FOUND:
		    std::cout << "RESOURCE_NOT_FOUND\n";
                    break;
                case Aws::Lambda::LambdaErrors::TOO_MANY_REQUESTS:
		    std::cout << "TOO_MANY_REQUESTS\n";
                    break;
                default:
		    std::cout << "Other error\n";
                    break;
            }
	    std::cout << "Lambda : "
		      << i
		      << " Exception : "
		      << aws_error.GetExceptionName()
		      << " Message : "
		      << aws_error.GetMessage()
		      << std::endl;
	}
	writeToFile(filename, i, lir);
	i++;
    }

    endTime = getTime();
    std::cout << "Total execution time of " << nLambdas << ": " << elapsed(endTime, beginTime) << std::endl;

    init_locks();

    std::cout << "Average time including network latency : " << average(diff_times_lambda_network) << std::endl;
    std::cout << "Average time excluding network latency : " << average(diff_times_lambda_only)    << std::endl;
    std::cout << "Total no. of success : " << success << " and total no. of failures : " << failures << std::endl;
    std::cout << std::endl;

    return 0;  
}
