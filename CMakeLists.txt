cmake_minimum_required(VERSION 2.6)
project(cast6)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(cast6
        src/cast6.cpp
        src/cast6.h
        src/cast6_s_boxes.h
        src/cbc.cpp
        src/cbc.h
        src/crypto_interface.cpp
        src/crypto_interface.h
        src/main.cpp
        src/test_case_rfc2612.h
        src/types.h
        src/utils.cpp
        src/utils.h)
