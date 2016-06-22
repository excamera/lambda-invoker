#include "RequestParams.hpp"

RequestParams::RequestParams()
{
  maxRetries       = 3;
  attemptedRetries = 0;
}

RequestParams::RequestParams(int m)
{
  maxRetries = m;
}

void RequestParams::setMaxRetries(int m)
{
  maxRetries = m;
}

void RequestParams::setAttemptedRetries(int a)
{
  attemptedRetries = a;
}

void RequestParams::incrAttemptedRetries()
{
  attemptedRetries++;
}

int RequestParams::getMaxRetries()
{
  return maxRetries;
}

int RequestParams::getAttemptedRetries()
{
  return attemptedRetries;
}

void RequestParams::setS3Key(std::string s)
{
  s3Key = s;
}

std::string RequestParams::getS3Key()
{
  return s3Key;
}

bool RequestParams::validateS3Key(std::string s)
{
  return true;
}

std::string RequestParams::get_input_bucket_name()
{
  return input_bucket_name;
}

std::string RequestParams::get_output_bucket_name()
{
  return output_bucket_name;
}

void RequestParams::set_input_bucket_name(std::string s)
{
  input_bucket_name = s;
}

void RequestParams::set_output_bucket_name(std::string s)
{
  output_bucket_name = s;
}
