cmake_minimum_required(VERSION 3.8)

project(myRtspClient)

#g++ common_example.cpp -I ../myRtspClient/include ../myRtspClient/libmyRtspClient.a -I ../third_party/JRTPLIB/src ../third_party/JRTPLIB/src/libjrtp.a

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/third_party/Base64_live555/include
${CMAKE_SOURCE_DIR}/third_party/md5/include
${CMAKE_SOURCE_DIR}/third_party/JRTPLIB/src
${CMAKE_SOURCE_DIR}/third_party/libregex
${CMAKE_BINARY_DIR}/third_party/JRTPLIB/src)
link_directories(
${CMAKE_BINARY_DIR}/third_party/JRTPLIB/src
)

file(GLOB SOURCES "*.cpp" 
"${CMAKE_SOURCE_DIR}/third_party/Base64_live555/*.cpp" 
"${CMAKE_SOURCE_DIR}/third_party/md5/*.cpp" 
"${CMAKE_SOURCE_DIR}/third_party/libregex/regex.c") 

add_library(myRtspClient STATIC ${SOURCES})

if(MSVC)
set (ext_libs ws2_32)
else(MSVC)
set (ext_libs)
endif(MSVC)

target_link_libraries(myRtspClient 
PRIVATE jrtplib
PRIVATE ${ext_libs}
)