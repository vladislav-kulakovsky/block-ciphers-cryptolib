cmake_minimum_required(VERSION 3.13)
project(cast256)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cast256
        src/blowfish.h
        src/cast6.cpp
        src/cast6.h
        src/cast6_s_boxes.h
        src/cbc.cpp
        src/cbc.h
        src/crypto_interface.cpp
        src/crypto_interface.h
        src/ecb.cpp
        src/ecb.h
        src/main.cpp
        src/test_case_rfc2612.h
        src/types.h
        src/utils.cpp
        src/utils.h src/blowfish.cpp src/blowfish_const.h)