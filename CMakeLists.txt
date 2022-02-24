cmake_minimum_required(VERSION 3.20)
project(cpython_toy C)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set (Object_src 
src/Object/_obj_base_.h 
src/Object/PyObject.h
src/Object/PyIntObject.h src/Object/PyIntObject.c
src/Object/_obj_core_.h src/Object/_obj_core_.c
src/Object/PyStringObject.h src/Object/PyStringObject.c)

set (test_src src/test/PyIntObject_test.c)

message(">>!found /src/Object file ${Object_src}")
message(">>!found /src/test file ${test_src}")

add_executable(cpython_toy ${Object_src} ${test_src})