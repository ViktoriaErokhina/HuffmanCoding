//
// Created by Viktoria Erokhina on 19.04.17.
//

#include "../Compresser/Encoder.h"
#include "../Compresser/Decoder.h"
#include "../Compresser/FileUtil.h"
#include <iostream>
#include <cstring>

void compress(char *input, char *output) {
    FileUtil out(output, "wb");
    adder ad;
    std::vector<unsigned char> text;
    {
        FileUtil in(input, "rb");
        int cnt = 0;
        while (in.read_block(in.MAX_CHAR, text)) {
            ad.add_text(text);
            cnt += text.size();
            //std::cerr << cnt << std::endl;
        }
        //std::cerr << "!" << std::endl;
    }
    Encoder en(ad);
    en.build_tree();

    std::vector<int> freq;
    en.get_freq(freq);
    out.write_block(freq, "\n");

    FileUtil in(input, "rb");
    while (in.read_block(in.MAX_CHAR, text)) {
        //std::cerr << "@" << std::endl;
        //std::cerr << "HELLO" << std::endl;
        std::vector<unsigned char> encoded_text;
        //std::cerr << "before encode" << std::endl;
        en.encode(text, encoded_text);
        //std::cerr << "after encode" << std::endl;
        out.write_block(encoded_text, "");
    }
}

void decompress(char *input, char *output) {
    FileUtil in(input, "rb");
    FileUtil out(output, "wb");


    std::vector<int> freq;
    try {
        in.read_block(256, freq);
    } catch (std::invalid_argument const &e) {
        throw;
    }
    unsigned char end;
    in.read_char(end);
    if (end != '\n') {
        throw std::invalid_argument("wrong file to decompress");
    }
    int cnt = 0;
    for (int i = 0; i < freq.size(); ++i) {
        cnt += freq[i];
        if (freq[i] < 0) {
            throw std::invalid_argument("wrong file to decompress");
        }
    }

    Decoder dec(freq);
    while (true) {
        bool eof = false;
        std::vector<unsigned char> ans;
        while ((int)ans.size() < in.MAX_CHAR && cnt > 0) {
            if (dec.is_empty_buff()) {
                unsigned char symb;
                if (!in.read_char(symb)) {
                    eof = true;
                    break;
                }
                dec.append_buff(symb);
            }
            std::pair <bool, unsigned char> p = dec.get_symb_from_buff();
            if (p.first) {
                ans.push_back(p.second);
                cnt--;
            }
        }
        dec.clear_buff();
        out.write_block(ans, "");
        if (eof || cnt <= 0) {
            break;
        }
    }
    if (cnt != 0) {
        throw std::invalid_argument("wrong file to decompress");
    }
}

int main(int argc, char **argv) {
    double t = clock();
    if (argc != 4) {
        std::cout << "count of arguments is not equal to 4" << std::endl;
        return 0;
    }

    char *mode = argv[1];
    char *inputfile = argv[2];
    char *outputfile = argv[3];

    if (strcmp(mode, "compress") == 0) {
        compress(inputfile, outputfile);
    } else if (strcmp(mode, "decompress") == 0) {
        try {
            decompress(inputfile, outputfile);
        } catch (std::invalid_argument e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    } else {
        std::cout << "incorrect mode" << std::endl;
    }

    std::cerr << (clock() - t) / CLOCKS_PER_SEC << std::endl;

    return 0;
}