#ifndef LAMBDA_INVOCATION_RECORD_H
#define LAMBDA_INVOCATION_RECORD_H

#include <aws/lambda/LambdaClient.h>
#include <aws/core/client/AWSError.h>
#include <aws/core/Core_EXPORTS.h>
#include <chrono>

using namespace Aws::Client;
using namespace Aws::Lambda;
using namespace std::chrono;

class LambdaInvocationRecord {
  public:
    LambdaInvocationRecord();
  public:
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;
    double start_time_inside;
    double end_time_inside;
    bool result;
    std::string str;
    Aws::Client::AWSError<Aws::Lambda::LambdaErrors> aws_error;
};

void writeToFile(char* filename, int n, LambdaInvocationRecord lir);

#endif
