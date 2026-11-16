#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "../utils/components.h"
#include "../utils/utils.h"

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

inline std::string line;
inline std::string instruction, operand1, operand2;
inline int ram_counter = 0;
std::vector<std::string> inst_ra_rb = {"ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP", "LD", "ST", "IO"};


inline void encode_inst_ra_rb(std::istringstream& iss) {
	iss >> operand1 >> operand2;
	ram.ram256[ram_counter] = (ADD << 4) | encode_ra(operand1) | encode_rb(operand2);
	std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;
}

inline void assemble(std::string source_code) {
        std::istringstream input(source_code);
        ram_counter = 0;

        while(std::getline(input, line)) {
                std::istringstream iss(line);
                iss >> instruction;

                if (std::find(inst_ra_rb.begin(), inst_ra_rb.end(), instruction) != inst_ra_rb.end()) { 
			encode_inst_ra_rb(iss);
		}
		else if (instruction == "DATA") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (DATA << 4) | encode_ra(operand1);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]);
			ram_counter++;
			ram.ram256[ram_counter] = std::stoi(operand2);
			std::cout << "  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }
		else if (instruction == "JMPR") {
                        iss >> operand1;
                        ram.ram256[ram_counter] = (JMPR << 4) | encode_rb(operand1);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }
		else if (instruction == "JMP") {
                        iss >> operand1;
                        ram.ram256[ram_counter] = (JMP << 4);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]);
		 	ram_counter++;
			ram.ram256[ram_counter] = std::stoi(operand1);
			std::cout << "  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }
		else if (instruction == "CLF") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (CLF << 4) | 0;
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }

        }
}
