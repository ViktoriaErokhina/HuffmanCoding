//
// Created by Viktoria Erokhina on 29.04.17.
//

#include <iostream>
#include "FileUtil.h"
#include <string.h>
#include <stdio.h>

FileUtil::FileUtil(const char *filename, const char *mode) {
    file = fopen(filename, mode);
    if (file == NULL) {
        throw std::invalid_argument("error while opening file");
    }
    this->mode = mode[0];
}

template<typename T>
bool FileUtil::read_block(int size, std::vector<T> &text) {
};

template<> bool FileUtil::read_block(int size, std::vector<unsigned char> &text) {
    text.clear();
    if (mode == 'w') {
        throw std::invalid_argument("trying to read file in writing mode");
    }
    text.resize((unsigned long) size);
    size_t cnt_read = fread(text.data(), 1, (size_t)size, file);
    text.erase(text.begin() + cnt_read, text.end());
    return cnt_read > 0;
}

template<> bool FileUtil::read_block(int size, std::vector<int> &text) {
    text.clear();
    if (mode == 'w') {
        throw std::invalid_argument("trying to read file in writing mode");
    }
    int token;
    while (size > 0 && fscanf(file, "%d", &token) > 0) {
        text.push_back(token);
        --size;
    }
    return (int)text.size() > 0;
}

template<typename T>
void FileUtil::write_block(std::vector<T> &text, const char *sep) {
};

template<> void FileUtil::write_block(std::vector<unsigned char> &text, const char *sep) {
    if (strlen(sep) == 0) {
        fwrite(text.data(), sizeof(char), text.size(), file);
    } else {
        int i = 0;
        while (i < (int) text.size()) {
            fprintf(file, "%c%s", text[i], sep);
            ++i;
        }
    }
}

template<> void FileUtil::write_block(std::vector<int> &text, const char *sep) {
    int i = 0;
    while (i < (int) text.size()) {
        fprintf(file, "%d%s", text[i], sep);
        ++i;
    }
}

FileUtil::~FileUtil() {
    fclose(file);
}

bool FileUtil::read_char(unsigned char &c) {
    return fscanf(file, "%c", &c) > 0;
}
