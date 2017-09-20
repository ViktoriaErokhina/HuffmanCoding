//
// Created by Viktoria Erokhina on 19.04.17.
//

#include <set>
#include "Decoder.h"

Decoder::Decoder(const std::vector<int> &frequencies) {
    for (int i = 0; i < MAX_CHAR; i++) {
        freq[i] = frequencies[i];
    }
    for (int i = 0; i < MAX_VERTEX; ++i) {
        parent[i] = -1;
        children[i].first = children[i].second = -1;
    }
    build_tree();
}

void Decoder::build_tree() {
    std::set<std::pair<int, int> > sorted;
    for (int i = 0; i < MAX_CHAR; ++i) {
        symbols[i] = i;
        sorted.insert(std::make_pair(freq[i], i));
    }
    int cur = MAX_CHAR;
    for (int i = 0; i < MAX_CHAR - 1; ++i) {
        std::pair <int, int> v1 = *sorted.begin();
        sorted.erase(v1);
        std::pair <int, int> v2 = *sorted.begin();
        sorted.erase(v2);
        parent[v1.second] = parent[v2.second] = cur;
        children[cur].first = v1.second;
        children[cur].second = v2.second;
        sorted.insert(std::make_pair(v1.first + v2.first, cur++));
    }
    root = cur - 1;
    cur_vrtx = root;
}

void Decoder::append_buff(unsigned char s) {
    for (int i = 7; i >= 0; i--) {
        buff.push(bool((s >> i) & 1));
    }
}

std::pair<bool, unsigned char> Decoder::get_symb_from_buff() {
    while (!is_empty_buff()) {
        if (children[cur_vrtx] != std::make_pair(-1, -1)) {
            if (buff.front() == true) {
                cur_vrtx = children[cur_vrtx].second;
            } else {
                cur_vrtx = children[cur_vrtx].first;
            }
            buff.pop();
        } else {
            int tmp = cur_vrtx;
            cur_vrtx = root;
            return std::make_pair(true, (unsigned char)tmp);
        }
    }
    if (children[cur_vrtx] == std::make_pair(-1, -1)) {
        int tmp = cur_vrtx;
        cur_vrtx = root;
        return std::make_pair(true, (unsigned char)tmp);
    }
    return std::make_pair(false, 0);
}

bool Decoder::is_empty_buff() {
    return buff.size() == 0;
}

void Decoder::clear_buff() {
    while (buff.size() > 0) {
        buff.pop();
    }
}