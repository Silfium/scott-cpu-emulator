#include <cstdint>
#include <iostream>
#include <string>
#include "components.h"


//--------------------------------------------------------|
// parsing Instruction Register IR and decoding instruction
inline uint8_t get_opcode() {
	return cpu.ir.value >> 4;
}
inline uint8_t get_ra() {
        return (cpu.ir.value >> 2) & 3;
}
inline uint8_t get_rb() {
	return cpu.ir.value & 3;
}
inline void decode_ir() {
        uint8_t ra = get_ra();
        uint8_t rb = get_rb();
        uint8_t opcode = get_opcode();
}


//--------------------------------------------------------|
//utils for tests
inline void print_binary(uint8_t value) {
        for (int i = 7; i >= 0; i--) {
		if (i == 3) {std::cout << " ";}
                std::cout << ((value >> i) & 1);
	}
}
