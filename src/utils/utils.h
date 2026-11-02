#pragma once

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
	
	if (opcode >= 0b00001000) { //it means its arithmetic/logic and uses the ALU
		//stepper in 4
		cpu.general_purpose[rb].enable();
		cpu.tmp.set();
		//stepper in 5
		cpu.general_purpose[ra].enable();
		cpu.alu(opcode); //acc is set in the alu func no need to do it here
		//stepper in 6
		cpu.acc.enable();
		cpu.general_purpose[rb].set();
	}
	else {
		switch (opcode) {
			case 0: // load
				// stepper in 4
				cpu.general_purpose[ra].enable();
				ram.mar.set();
				// stepper in 5
				ram.enable();
				cpu.general_purpose[rb].set();
				// no step 6
				break;

			case 1: //store
				//stepper in 4
				cpu.general_purpose[ra].enable();
				ram.mar.set();
				//stepper in 5
				cpu.general_purpose[rb].enable();
				ram.set();
				// no step 6
				break;

			case 2: // data
				// not documented yet
				break;

			case 3:// jump to rb



			case 4: // jump with addr
				// stepper in 4
				cpu.iar.enable();
			        ram.mar.set();
				//stepper in 5
				ram.set();
				cpu.iar.set();
				//no step 6
				break;

			case 5: // jump all other variants
				break;

			case 6: //clear flags
				// stepper in 4
				cpu.flags.value = 0;
				// no step 5 and 6
				break;

			case 7: // io
				// not documented yet
				break;
		}
	}
}


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
