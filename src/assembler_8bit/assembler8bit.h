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
                        ram.ram256[ram_counter] = (ADD << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }
		else if (instruction == "SHR") {
			iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (SHR << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;	
		}
		else if (instruction == "SHL") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (SHL << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "NOT") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (NOT << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "AND") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (AND << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "OR") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (OR << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "XOR") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (XOR << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "CMP") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (CMP << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "LD") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (LD << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "ST") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (ST << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "DATA") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (DATA << 4) | encode_ra(operand1);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]);
			ram_counter++;
			ram.ram256[ram_counter] = std::stoi(operand2);
			std::cout << "  " << print_binary(ram.ram256[ram_counter]);
                }
		else if (instruction == "JMPR") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (JMPR << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;
                }
		else if (instruction == "JMP") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (JMP << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "CLF") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (CLF << 4) | 0;
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }
		else if (instruction == "IO") {
                        iss >> operand1 >> operand2;
                        ram.ram256[ram_counter] = (IO << 4) | encode_ra(operand1) | encode_rb(operand2);
                        std::cout << line << "  :  " << print_binary(ram.ram256[ram_counter]) << std::endl;       
                }


        }
}
