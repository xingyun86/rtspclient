# CMakeList.txt : CMake project for RtspClient, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/myRtspClient/include
	${CMAKE_SOURCE_DIR}/third_party/libregex
)
link_directories(
	${CMAKE_BINARY_DIR}/myRtspClient
	${CMAKE_BINARY_DIR}/third_party/JRTPLIB/src
)
# Add source to this project's executable.
add_executable (RtspClientDemo "RtspClientDemo.cpp" "RtspClientDemo.h")

target_link_libraries(RtspClientDemo 
PRIVATE myRtspClient
PRIVATE jrtplib
)
# TODO: Add tests and install targets if needed.
