//
// Copyright Jippe Heijnen (07/10/2020).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//

#include <hwlib.hpp>

extern "C" void uart_put_char(char c) {
    hwlib::cout << c;
}

extern "C" void decompressor(char* buffer);


int main() {
    char a[40];
    hwlib::wait_ms(1000);
    decompressor(a);
    hwlib::cout << "done\n";
}