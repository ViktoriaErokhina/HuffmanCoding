//
// Created by Viktoria Erokhina on 19.04.17.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include <vector>
#include <queue>

class Decoder {
private:
    static const int MAX = 256;
    static const int MAX_VERTEX = MAX * 2 + 5;
    int symbols[MAX];
    int parent[MAX_VERTEX];
    std::pair <int, int> children[MAX_VERTEX];
    int freq[MAX];
    std::vector<bool> codes[MAX];
    int root;
    std::queue <bool> buff;
    int cur_vrtx;
public:
    Decoder(const std::vector<int> &frequencies);
    static const int MAX_CHAR = 256;
    void build_tree();
    void append_buff(unsigned char s);
    std::pair <bool, unsigned char> get_symb_from_buff();
    bool is_empty_buff();
    void clear_buff();
};


#endif //HUFFMAN_DECODER_H
