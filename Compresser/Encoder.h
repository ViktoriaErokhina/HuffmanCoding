//
// Created by Viktoria Erokhina on 19.04.17.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <vector>

struct adder {
    void add_text(std::vector<unsigned char> &text);
    int freq[256];
    adder() {
        for (int i = 0; i < 256; i++) {
            freq[i] = 0;
        }
    }
};

class Encoder {
private:
    adder ad;
    static const int MAX_CHAR = 256;
    static const int MAX_VERTEX = MAX_CHAR * 2 + 5;
    int symbols[MAX_CHAR];
    int parent[MAX_VERTEX];
    std::pair <int, int> children[MAX_VERTEX];
    std::vector<bool> codes[MAX_CHAR];
    void fill_codes();
public:
    Encoder(adder const&);
    void build_tree();
    void encode(const std::vector<unsigned char> &text, std::vector<unsigned char> &encoded_text);
    void get_freq(std::vector<int> &frequencies);
};


#endif //HUFFMAN_ENCODER_H
