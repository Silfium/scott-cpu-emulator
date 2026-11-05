#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include "components.h"



//--------------------------------------------------------|
//utils for tests
inline std::string print_binary(uint8_t value) {
    std::string result;
    for (int i = 7; i >= 0; i--) {
        if (i == 3) result += " ";
        result += ((value >> i) & 1) ? '1' : '0';
    }
    return result;
}
