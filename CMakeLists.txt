cmake_minimum_required(VERSION 3.10.0)
project(boosthub)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -O2")

FIND_PACKAGE(Threads)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

 
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

FILE(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
ADD_EXECUTABLE(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)