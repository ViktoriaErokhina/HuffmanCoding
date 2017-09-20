#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

enum TYPE {
    FILEF,
    GEN
};

FILE *f1;
FILE *f2;
FILE *gen;

bool diff(string f1n, string f2n) {
    string fname = "check_diff.txt";
    string str = "diff " + f1n + " " + f2n + " 2> " + fname;
    system(str.c_str());
    FILE *checkDiff = fopen(fname.c_str(), "rb");
    char c;
    int g = fscanf(checkDiff, "%c", &c);
    fclose(checkDiff);
    if (g > 0)
        return false;
    return true;
}

struct test {
private:
    int size;
    int max_code, min_code;
    std::string filename;
    TYPE type;
public:
    test () {};
    test(int max_code, int min_code) {
        this -> max_code = max_code;
        this -> min_code = min_code;
        type = GEN;
    }
    test (std::string filename) {
        this -> filename = filename;
        type = FILEF;
    }
    void set_size(int sz) {
        this -> size = sz;
    }
    TYPE get_type() {
        return this->type;
    }
    bool testing() {
        if (type == FILEF) {
            std::string str = "./ConsoleUtil compress " + filename + " encoded.txt";
            system(str.c_str());
            str = "./ConsoleUtil decompress ";
            str += "encoded.txt ";
            str += ("decoded-" + filename);
            system(str.c_str());
            return diff(filename, "decoded-" + filename);
        } else {
            int len = max_code - min_code + 1;
            gen = fopen("gen.txt", "wb");
            for (int i = 0; i < size; ++i) {
                unsigned char nxt = (unsigned char)(rand() % len + min_code);
                fprintf(gen, "%c", nxt);
            }
            fclose(gen);
            std::string str = "./ConsoleUtil compress gen.txt encoded.txt";
            system(str.c_str());
            str = "./ConsoleUtil decompress ";
            str += "encoded.txt ";
            str += "decoded-gen.txt";
            system(str.c_str());
            return diff("gen.txt", "decoded-gen.txt");
        }
    }
};

int main(int argc, char ** argv) {
    int NUMBER_OF_TESTS = 20;
    srand((unsigned int)time(NULL));
    std::vector<test> tests;
    //tests.push_back(std::string("a.bmp"));
    //tests.push_back(std::string("nature.jpg"));
    //tests.push_back(std::string("term1-cpp.pdf"));
    //tests.push_back(std::string("rrr.cpp"));
    //tests.push_back(std::string("big_file.txt"));
    tests.push_back(test(10, 10));
    tests.push_back(test(0, 10));
    tests.push_back(test(48, 60));
    tests.push_back(test(65, 90));
    int n = tests.size();
    for (int i = 0; i < NUMBER_OF_TESTS - n + 1; ++i) {
        int l = rand() % 256;
        int r = rand() % 256;
        tests.push_back(test(min(l, r), max(l, r)));
    }
    for (size_t i = 0; i < tests.size(); ++i) {
        if (tests[i].get_type() != FILEF) {
            tests[i].set_size(rand() % 10000000);
        }
    }
    for (size_t i = 0; i < tests.size(); ++i) {
        printf("\n\n");
        printf("Testing %d....\n", (int)i + 1);
        bool isOk = tests[i].testing();
        printf("Result for test %d = ", (int)i + 1);
        if (!isOk) {
            puts("FAIL!");
            break;
        } else {
            puts("OK!");
        }
    }
    return 0;
}