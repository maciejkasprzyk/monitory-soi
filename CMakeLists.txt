cmake_minimum_required(VERSION 3.13)
project(monitory)

set(CMAKE_CXX_STANDARD 14)

add_executable(monitory main.cpp SynchronizedQueue.cpp SynchronizedQueue.h queue.cpp queue.h)

set(CMAKE_CXX_FLAGS "-lrt")

target_link_libraries(${PROJECT_NAME} pthread)