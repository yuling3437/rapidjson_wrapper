cmake_minimum_required(VERSION 2.8)
project(test)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)

MESSAGE( "src files :${SRC_LIST}")

INCLUDE_DIRECTORIES(/opt/IPC.git/ip_base/base)

ADD_DEFINITIONS( -g -W -Wall -std=c++11)

ADD_EXECUTABLE(test ${SRC_LIST})

target_link_libraries(test)
