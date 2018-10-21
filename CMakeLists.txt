cmake_minimum_required(VERSION 3.12)
project(sameEncoder)

set(CMAKE_CXX_STANDARD 17)

link_libraries(sndfile)

add_executable(sameEncoder main.cpp audio.cpp audio.h eas.h eas.cpp Utils.cpp Utils.h)