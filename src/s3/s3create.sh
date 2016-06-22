i=1
n=900

while [ $i -lt $n ]
do
  filename=$(cat /dev/urandom | tr -cd 'a-f0-9' | head -c 20)
  dd if=/dev/zero of=$filename count=1024 bs=1024
  aws s3 cp $filename s3://keith-lambda-testing/
  rm $filename
  i=$((i+1))
done

aws s3 ls s3://keith-lambda-testing/
