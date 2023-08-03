cmake_minimum_required(VERSION 3.0)
project(HTTPServer)

set(LIBEVENT_DIR /usr/local/lib)
include_directories(${LIBEVENT_DIR}/include)
link_directories(${LIBEVENT_DIR}/lib)

set(SOURCES testhttp.cpp)

add_executable(HTTPServer ${SOURCES})
target_link_libraries(HTTPServer event)
