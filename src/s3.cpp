#include <vector>

using namespace std;

static std::vector
ListObjects(const Aws::String& bucketName)
{
  Aws::S3::S3Client Client{config};
  ListObjectsRequest listObjectsRequest;
  listObjectsRequest.SetBucket(bucketName);

  ListObjectsOutcome listObjectsOutcome = Client->ListObjects(listObjectsRequest);

  if (!listObjectsOutcome.IsSuccess())
  {
    return;
  }

  for (const auto& object : listObjectsOutcome.GetResult().GetContents())
  {
    vector.push_back(object.GetKey());
  }

  return vector;
}
