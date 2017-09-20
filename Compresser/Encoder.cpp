//
// Created by Viktoria Erokhina on 19.04.17.
//

#include <set>
#include <algorithm>
#include <iostream>
#include "Encoder.h"

Encoder::Encoder(adder const& b) {
    for (int i = 0; i < MAX_CHAR; ++i) {
        ad.freq[i] = b.freq[i];
    }
    for (int i = 0; i < MAX_VERTEX; ++i) {
        parent[i] = -1;
        children[i].first = children[i].second = -1;
    }
}

void Encoder::build_tree() {
    std::set<std::pair<int, int> > sorted;
    for (int i = 0; i < MAX_CHAR; ++i) {
        symbols[i] = i;
        sorted.insert(std::make_pair(ad.freq[i], i));
    }
    int cur = MAX_CHAR;
    for (int i = 0; i < MAX_CHAR - 1; ++i) {
        std::pair<int, int> v1 = *sorted.begin();
        sorted.erase(v1);
        std::pair<int, int> v2 = *sorted.begin();
        sorted.erase(v2);
        parent[v1.second] = parent[v2.second] = cur;
        children[cur].first = v1.second;
        children[cur].second = v2.second;
        sorted.insert(std::make_pair(v1.first + v2.first, cur++));
    }
    fill_codes();
}

void Encoder::fill_codes() {
    for (int i = 0; i < MAX_CHAR; ++i) {
        int cur_vertex = i;
        int cur_parent = parent[i];
        while (cur_parent != -1) {
            codes[i].push_back(children[cur_parent].first != cur_vertex);
            cur_vertex = cur_parent;
            cur_parent = parent[cur_vertex];
        }
        reverse(codes[i].begin(), codes[i].end());
    }
}

void Encoder::encode(const std::vector<unsigned char> &text, std::vector<unsigned char> &encoded_text) {
    int cnt = 0;
    int new_symb = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        int symb = (int)text[i];
        //std::cerr << codes[symb].size() << std::endl;
        for (size_t j = 0; j < codes[symb].size(); ++j) {
            new_symb <<= 1;
            new_symb += codes[symb][j];
            ++cnt;
            if (cnt == 8) {
                encoded_text.push_back(static_cast<unsigned char>(new_symb));
                cnt = 0;
                new_symb = 0;
            }
        }
    }
    while (cnt > 0 && cnt < 8) {
        new_symb <<= 1;
        ++cnt;
    }
    if (cnt != 0) {
        encoded_text.push_back(new_symb);
    }
}

void Encoder::get_freq(std::vector<int> &frequencies) {
    for (int i = 0; i < MAX_CHAR; ++i) {
        frequencies.push_back(ad.freq[i]);
    }
}

void adder::add_text(std::vector<unsigned char> &text) {
    for (size_t i = 0; i < text.size(); ++i) {
        ++freq[text[i]];
    }
}
