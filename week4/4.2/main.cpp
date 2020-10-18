#include <iostream>
#include <fstream>
#include <array>

#include "compressor.hpp"
#include "decompressor.hpp"

int main(void) {

    lz_compressor<2048> compressor;
    lz_decompressor decompressor;
    std::ifstream f1;
    f1.open("wilhelmus.txt");
    if (!f1.is_open()) {
        std::cerr << "input file not opened";
        return -1;
    }

    std::ofstream f2;
    f2.open("compressed.txt");
    if (!f2.is_open()) {
        std::cerr << "output file not opened";
        return -1;
    }

    compressor.compress(
            [&f1]() -> int {
                auto c = f1.get();
                return f1.eof() ? '\0' : c;
            },
            [&f2](char c) { f2.put(c); }
    );

    f1.close();
    f2.close();

    f1.open("compressed.txt");
    if( ! f1.is_open()){
        std::cerr << "input file not opened";
        return -1;
    }

    decompressor.decompress(
            [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
            []( char c ){ std::cout << c; }
    );

}