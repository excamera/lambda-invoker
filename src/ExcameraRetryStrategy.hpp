//#ifndef EXCAMERA_RETRY_STRATEGY_H
//#define EXCAMERA_RETRY_STRATEGY_H

#include <aws/lambda/LambdaClient.h>
#include <aws/core/client/AWSError.h>
#include <aws/core/Core_EXPORTS.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/core/utils/UnreferencedParam.h>
#include <aws/core/client/AWSErrorMarshaller.h>

using namespace Aws::Client;
using namespace Aws::Lambda;
using namespace Aws::Utils;

class ExcameraRetryStrategy : public RetryStrategy {
    public:
        ExcameraRetryStrategy(long maxRetries = 10, long scaleFactor = 25);
        bool ShouldRetry(const Aws::Client::AWSError<CoreErrors>& error, long attemptedRetries) const;        
	long CalculateDelayBeforeNextRetry(const Aws::Client::AWSError<CoreErrors>& error, long attemptedRetries) const;
    
    private:
        long m_scaleFactor;
        long m_maxRetries;
};

//#endif
