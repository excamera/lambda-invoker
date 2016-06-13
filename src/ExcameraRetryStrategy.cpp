#include "ExcameraRetryStrategy.hpp"

ExcameraRetryStrategy::ExcameraRetryStrategy(long maxRetries = 10,
					     long scaleFactor = 25) :
  m_scaleFactor(scaleFactor), 
  m_maxRetries(maxRetries)
{
}

bool 
ExcameraRetryStrategy::ShouldRetry(const AWSError<CoreErrors>& error,
				   long attemptedRetries) 
				   const
{
  if (attemptedRetries >= m_maxRetries)
  {
    return false;
  }

  return error.ShouldRetry();
}

long
ExcameraRetryStrategy::CalculateDelayBeforeNextRetry(const AWSError<CoreErrors>& error,
						     long attemptedRetries)
						     const
{
  AWS_UNREFERENCED_PARAM(error);

  if (attemptedRetries == 0)
  {
    return 0;
  }

  return (1 << attemptedRetries) * m_scaleFactor;
}
