cmake_minimum_required(VERSION 2.8)
project(mrs)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--whole-archive /usr/local/lib/libcaffe.a -Wl,--no-whole-archive -Wall -Wextra -pedantic")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

include_directories(
  /home/noega/Desktop/stasm/Headers
)

add_subdirectory(Source)
