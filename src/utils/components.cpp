#include "components.h"
#include <cstdint>
#include <limits>


void Reg::set() {value = system_bus;}
void Reg::enable() {system_bus = value;}

void flagReg::set(flags flag) {
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
	//stepper in 2
		//enable ram
		//ir = ram output
	//stepper in 3
	acc.enable();
	iar.set();
	//stepper in 7
	stepper = 1;
}
void CPU::control_section() {
	
}
void CPU::alu(uint8_t op) {
	switch(op) {
		case 0x00:
			//ADD
			if (system_bus > std::numeric_limits<uint8_t>::max() - tmp.value) {flagsReg.set(CARRY_OUT);}
			acc.value = tmp.value + system_bus;
			break;
		case 0x01:
			//SHR
			acc.value = system_bus >> 1;
			break;
		case 0x02:
			//SHL
			acc.value = system_bus << 1;
			break;
		case 0x03:
			//NOT
			acc.value = ~system_bus;
			break;
		case 0x04:
			//AND
			acc.value = system_bus & tmp.value;
			break;
		case 0x05:
			//OR
			acc.value = system_bus | tmp.value;
			break;
		case 0x06:
			//XOR
			acc.value = system_bus ^ tmp.value;
			break;
		case 0x07:
			//CMP
			break;
	}
	stepper = 1;
}
void CPU::reset() {
	r0.value = 0; r1.value = 0; r2.value = 0; r3.value = 0;
	acc.value   = 0;
	tmp.value   = 0;
	ir.value    = 0;
	iar.value   = 0;
}




