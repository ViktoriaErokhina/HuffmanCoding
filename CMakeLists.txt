cmake_minimum_required(VERSION 3.7)
project(Huffman)

set(CMAKE_CXX_STANDARD 11)

set(S_EXE Console/main.cpp)
set(S_LIB Compresser/Encoder.cpp)
set(S_KEK Compresser/Decoder.cpp Compresser/FileUtil.cpp Compresser/FileUtil.h)


add_library(HuffmanCompresser STATIC ${S_LIB} ${S_KEK})
add_executable(ConsoleUtil ${S_EXE})

target_link_libraries(ConsoleUtil HuffmanCompresser)
