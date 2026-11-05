#include "components.h"
#include "utils.h"
#include <cstdint>
#include <limits>



//-------------------------------------|
//-------------------------------------|
// register

void Reg::set()    {value = system_bus;}
void Reg::enable() {system_bus = value;}

void flagReg::set(flagType flag) {
	switch(flag) {
		case CARRY_OUT:
		       value = value | CARRY_OUT;
		       break;
		case A_LARGER:
			value = value | A_LARGER;
			break;
	 	case EQUAL:
			value = value | EQUAL;
			break;
		case ZERO:
			value = value | ZERO;
			break;
	}
}



//-----------------------------------|
//-----------------------------------|
// CPU

void CPU::step_cycle() {
	//stepper in 1
	bus1 = true;
	iar.enable();
	alu(0);  // rework this part need to figure out how to get the bitch ass bus 1 involved
	ram.mar.set();
	bus1 = false;
	//stepper in 2
        ram.enable();
	ir.set();
	//stepper in 3
	acc.enable();
	iar.set();
	// stepper in 4
	decode_ir();
	//stepper in 7
	stepper = 1;
}

// decoding ir utils
uint8_t CPU::get_opcode() {
        return ir.value >> 4; }
uint8_t CPU::get_ra() {
        return (ir.value >> 2) & 3; }
uint8_t CPU::get_rb() {
        return ir.value & 3; }
// decoding ir itself and running the remaining steps
void CPU::decode_ir() {
        uint8_t ra = get_ra();
        uint8_t rb = get_rb();
        uint8_t opcode = get_opcode();

        if (opcode >= 0b00001000) { //it means its arithmetic/logic and uses the ALU
                //stepper in 4
                general_purpose[rb].enable();
                tmp.set();
                //stepper in 5
                general_purpose[ra].enable();
                alu(opcode, false); //acc is set in the alu func no need to do it here
                //stepper in 6
                acc.enable();
                general_purpose[rb].set();
        }
        else {
                switch (opcode) {
                        case 0: // load
                                // stepper in 4
                                general_purpose[ra].enable();
                                ram.mar.set();
                                // stepper in 5
                                ram.enable();
                                general_purpose[rb].set();
                                // no step 6
                                break;

                        case 1: //store
                                //stepper in 4
                                general_purpose[ra].enable();
                                ram.mar.set();
                                //stepper in 5
                                general_purpose[rb].enable();
                                ram.set();
                                // no step 6
                                break;

                        case 2: // data
                                //step 4
				bus1 = true;
                                iar.enable();
                                alu(0);
                                ram.mar.set();
				bus1 = false;
                                // step 5
                                ram.enable();
                                general_purpose[rb].set();
                                // step 6
                                acc.enable();
                                iar.set();
                                break;

                        case 3:// jump to rb
                               // step 4
                               general_purpose[rb].enable();
                               iar.set();
                               // no step 5 and 6
                               break;

                        case 4: // jump with addr
                                // stepper in 4
                                iar.enable();
                                ram.mar.set();
                                //stepper in 5
                                ram.set();
                                iar.set();
                                //no step 6
                                break;

                        case 5: // jump all other variants
                                // first we 'and' the least segnificant nibble with the flag register to see if one of the conditions is met
                                uint8_t nibble = cpu.ir.value & 15; //seperate the nibble
                                if (nibble & flags.value) {
                                        // step 4
					bus1 = true;
                                        iar.enable();
                                        alu(0);
                                        ram.mar.set();
					bus1 = false;
                                        // step 5
                                        acc.enable();
                                        iar.set(); //questionalbe action need to check why
                                        // step 6
                                        ram.enable();
                                        iar.set();
                                } //else no action to be done
                                break;

                        case 6: //clear flags
                                // stepper in 4
                                flags.value = 0;
                                // no step 5 and 6
                                break;

                        case 7: // io
                                // not documented yet
                                break;
                }
        }
}


void CPU::alu(uint8_t op) {
	if (bus1) {
		acc.value = system_bus + 1;
		if (system_bus > std::numeric_limits<uint8_t>::max() - 1) { flags.set(CARRY_OUT); }
	}
	else {
		switch(op) {
			case 8://ADD
				if (system_bus > std::numeric_limits<uint8_t>::max() - tmp.value) { flags.set(CARRY_OUT);}
				acc.value = tmp.value + system_bus + (flags.value & CARRY_OUT); //flags and the carry out are to check if there's carryin
				break;
			case 9://SHR 
			        (flags.value & 1) ? (acc.value = system_bus >> 1 | 0b10000000)  :  (acc.value = system_bus >> 1); //is there a carry in
			        if (system_bus & 1) { (flags.set(CARRY_OUT); } 	
				break;
			case 10://SHL
			        (flags.value & 1) ? (acc.value = system_bus << 1 | 1)  :  (acc.value = system_bus << 1); // is there a carry in	
			        if (system_bus & 0b10000000) { (flags.set(CARRY_OUT); } 		
				break;
			case 11://NOT
				acc.value = ~system_bus;
				break;
			case 12://AND
				acc.value = system_bus & tmp.value;
				break;
			case 13://OR
				acc.value = system_bus | tmp.value;
				break;
			case 14://XOR
				acc.value = system_bus ^ tmp.value;
				break;
			case 15://CMP
				break;
		}
	}
	if (acc.value == 0) { flags.set(ZERO); }
}
void CPU::reset() {
	r0.value = 0; r1.value = 0; r2.value = 0; r3.value = 0;
	acc.value     = 0;
	tmp.value     = 0;
	ir.value      = 0;
	iar.value     = 0;
	flags.value   = 0;
	ram.mar.value = 0;
}


void RAM::enable() {system_bus = ram256[mar.value];}
void RAM::set()    {ram256[mar.value] = system_bus;}


