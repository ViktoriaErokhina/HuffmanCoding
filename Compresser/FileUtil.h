//
// Created by Viktoria Erokhina on 29.04.17.
//

#ifndef HUFFMAN_FILEUTIL_H
#define HUFFMAN_FILEUTIL_H


#include <cstdio>
#include <stdexcept>
#include <vector>

class FileUtil {
private:
    FILE *file;
    char mode;
public:
    FileUtil (const char *filename, const char *mode);
    ~FileUtil();
    static const int MAX_CHAR = (1 << 16);
    bool read_char(unsigned char &c);
    template <typename T> bool read_block(int size, std::vector <T> &text);
    template <typename T> void write_block(std::vector<T> &text, const char *sep);
};


#endif //HUFFMAN_FILEUTIL_H
