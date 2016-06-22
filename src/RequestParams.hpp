#include <aws/core/utils/StringUtils.h>

#include <string>

using namespace std;

class RequestParams
{
  public:
    RequestParams();
    RequestParams(int maxRetries);

    void setMaxRetries(int maxRetries);
    void setAttemptedRetries(int maxRetries);
    void setS3Key(std::string s);
    void set_input_bucket_name(std::string input_bucket_name);
    void set_output_bucket_name(std::string output_bucket_name);

    int getMaxRetries();
    int getAttemptedRetries();
    std::string getS3Key();
    std::string get_input_bucket_name();
    std::string get_output_bucket_name();

    void incrAttemptedRetries();
    bool validateS3Key(std::string s);

  public:
    int maxRetries;
    int attemptedRetries;
    std::string s3Key;
    std::string input_bucket_name;
    std::string output_bucket_name;
    std::string functionName;
    Aws::String input_s3_key;
};
