#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "../utils/components.h"

inline uint8_t encode_rb(std::string rb) {
        if (rb == "R0") {
                return 0;
        }
        else if (rb == "R1") {
                return 1;
        }
        else if (rb == "R2") {
                return 2;
        }
        else if (rb == "R3") {
                return 3;
        }
	return 0;
}

inline uint8_t encode_ra(std::string ra) {
        if (ra == "R0") {
                return 0 << 2;
        }
        else if (ra == "R1") {
                return 1 << 2;
        }
        else if (ra == "R2") {
                return 2 << 2;
        }
        else if (ra == "R3") {
                return 3 << 2;
        }
	return 0;
}

inline void assemble(std::string source_code) {
        std::istringstream input(source_code);
        std::string line;
        std::string instruction, operand1, operand2;

        int ram_counter = 0;

        while(std::getline(input, line)) {
                std::istringstream iss(line);
                iss >> instruction;

                if (instruction == "ADD") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = 128 | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << static_cast<int>(ram.ram256[ram_counter]) << std::endl;
                }
        }
}
