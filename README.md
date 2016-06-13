1. $ git clone https://github.com/excamera/lambda-invoker

2. $ cd lambda-invoker/build

3. $ env aws-sdk-cpp_DIR=<build_dir_of_aws-sdk-cpp> cmake ..

4. $ make clean && make all

5. This test invokes 900 lambdas each printing HELLOWORLD and writing to a sample text file

   $ ./lambda-invoke 900 HELLOWORLD sample.txt
	Starting AWS Lambda Test
	nLambdas : 900 lambda : HELLOWORLD
	Retry count : 10 and Scale Factor : 25
	Total execution time of 900: 1
	Average time including network latency : 0
	Average time excluding network latency : 0.00514712
	Total no. of success : 900 and total no. of failures : 0
