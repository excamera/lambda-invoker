#include "RequestParams.hpp"

RequestParams::RequestParams()
{
  maxRetries       = 3;
  attemptedRetries = 0;
}

RequestParams::RequestParams(uint32_t m)
{
  maxRetries = m;
}

void RequestParams::setMaxRetries(uint32_t m)
{
  maxRetries = m;
}

void RequestParams::setAttemptedRetries(uint32_t a)
{
  attemptedRetries = a;
}

void RequestParams::incrAttemptedRetries()
{
  attemptedRetries++;
}

uint32_t RequestParams::getMaxRetries()
{
  return maxRetries;
}

uint32_t RequestParams::getAttemptedRetries()
{
  return attemptedRetries;
}
