cmake_minimum_required(VERSION 2.8)

project(lambda-invoke)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -std=c++11 -fexceptions -fpermissive")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=output.map" CACHE INTERNAL "" FORCE)

find_package(aws-sdk-cpp)

add_executable(lambda-invoke src/main.cpp
			     src/ExcameraRetryStrategy.cpp
			     src/LambdaInvocationRecord.cpp
			     src/lib.cpp)

target_link_libraries(lambda-invoke aws-cpp-sdk-s3 aws-cpp-sdk-lambda)
