#include "components.h"
#include "utils.h"
#include <cstdint>
#include <limits>


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


void CPU::step_cycle() {

	//stepper in 1
	iar.enable();
	acc.value = iar.value + 1; // rework this part need to figure out how to get the bitch ass bus 1 involved
	ram.mar.set();

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
void CPU::control_section() {
	
}
void CPU::alu(uint8_t op) {
	switch(op) {
		case 8:
			//ADD
			if (system_bus > std::numeric_limits<uint8_t>::max() - tmp.value) {flags.set(CARRY_OUT);}
			acc.value = tmp.value + system_bus;
			break;
		case 9:
			//SHR
			acc.value = system_bus >> 1;
			break;
		case 10:
			//SHL
			acc.value = system_bus << 1;
			break;
		case 11:
			//NOT
			acc.value = ~system_bus;
			break;
		case 12:
			//AND
			acc.value = system_bus & tmp.value;
			break;
		case 13:
			//OR
			acc.value = system_bus | tmp.value;
			break;
		case 14:
			//XOR
			acc.value = system_bus ^ tmp.value;
			break;
		case 15:
			//CMP
			break;
	}
}
void CPU::reset() {
	r0.value = 0; r1.value = 0; r2.value = 0; r3.value = 0;
	acc.value   = 0;
	tmp.value   = 0;
	ir.value    = 0;
	iar.value   = 0;
}


void RAM::enable() {system_bus = ram256[mar.value];}
void RAM::set()    {ram256[mar.value] = system_bus;}


