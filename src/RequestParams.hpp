#include <stdint.h>

class RequestParams
{
  public:
    RequestParams();
    RequestParams(uint32_t maxRetries);
    void setMaxRetries(uint32_t maxRetries);
    void setAttemptedRetries(uint32_t maxRetries);
    uint32_t getMaxRetries();
    uint32_t getAttemptedRetries();
    void incrAttemptedRetries();
  private:
    uint32_t maxRetries;
    uint32_t attemptedRetries;
};
