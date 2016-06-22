static
std::shared_ptr<Aws::StringStream> createStreamData(const char* tag,
						    uint32_t size)
{
  Aws::StringStream patternStream;
  patternStream << "Multi-Part upload Test Part " << tag << ":" << std::endl;
  Aws::String pattern = patternStream.str();

  Aws::String scratchString;
  scratchString.reserve(fiveMbSize);

  uint32_t patternCopyCount = static_cast<uint32_t>(size/pattern.size()+1);
  for(uint32_t i = 0; i < patternCopyCount; i++)
  {
    scratchString.append( pattern );
  }

  std::shared_ptr<Aws::StringStream> streamPtr = Aws::MakeShared<Aws::StringStream>(ALLOCATION_TAG, scratchString);

  streamPtr->seekg(0);
  streamPtr->seekp(0, std::ios_base::end);

  return streamPtr;
}

static
Aws::String CalculateBucketName(const char* bucketPrefix)
{
  static Aws::String TimeStamp = DateTime::Now().CalculateLocalTimestampAsString("%Y%m%dt%H%M%Sz");
  return bucketPrefix + TimeStamp;
}

static
void createS3Bucket(const char* bucketName)
{
  Aws::String fullBucketName = CalculateBucketName(bucketName);
  
  CreateBucketRequest createBucketRequest;
  createBucketRequest.SetBucket(fullBucketName);
  createBucketRequest.SetACL(BucketCannedACL::private_);

  CreateBucketOutcome createBucketOutcome = Client->CreateBucket(createBucketRequest);
  ASSERT_TRUE(createBucketOutcome.IsSuccess());

  const CreateBucketResult& createBucketResult = createBucketOutcome.GetResult();
  ASSERT_TRUE(!createBucketResult.GetLocation().empty());
}

static
void putS3Object(const char* tag,
		 const char* obj_key)
{
  PutObjectRequest putObjectRequest;
  putObjectRequest.SetBucket(fullBucketName);

  uint32_t size = 1 * 1024 * 1024;
  std::shared_ptr<Aws::IOStream> bigStream = createStreamData(tag, size);

  putObjectRequest.SetBody(bigStream);
  putObjectRequest.SetContentLength(static_cast<long>(putObjectRequest.GetBody()->tellp()));
  putObjectRequest.SetContentMD5(HashingUtils::Base64Encode(HashingUtils::CalculateMD5(*putObjectRequest.GetBody())));
  putObjectRequest.SetContentType("text/plain");
  putObjectRequest.SetKey(obj_key);

  PutObjectOutcome putObjectOutcome = Client->PutObject(putObjectRequest);
  ASSERT_TRUE(putObjectOutcome.IsSuccess());
}

void create(const char* tag,
	    const char* bucketName)
{
    
}

