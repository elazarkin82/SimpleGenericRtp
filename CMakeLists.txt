cmake_minimum_required (VERSION 2.6)

project (SimpleGenericRtp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(lib_src
	${CMAKE_CURRENT_SOURCE_DIR}/src/BasicUdpStreamer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IComunicationObject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/BasicRtpStreamer.cpp
)

add_library(GenericRtpLib STATIC ${lib_src})

target_link_libraries(GenericRtpLib)

add_executable(udpTester tester/udpTester.cpp)

target_link_libraries(udpTester GenericRtpLib pthread)
