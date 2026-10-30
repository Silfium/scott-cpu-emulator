#include "components.h"
#include <cstdint>
#include <limits>



void::alu(uint8_t op) {
	switch(op) {
		case 0x00:
			//ADD
			//if (b > numeric_limits<uint8_t>::max() - a) {set overflow}
			acc = tmp + system_bus;
			break;
		case 0x01:
			//SHR
			acc = system_bus >> 1;
			break;
		case 0x02:
			//SHL
			acc = system_bus << 1;
			break;
		case 0x03:
			//NOT
			acc = ~system_bus;
			break;
		case 0x04:
			//AND
			acc = system_bus & tmp
			break;
		case 0x05:
			//OR
			acc = system_bus | tmp
			break;
		case 0x06:
			//XOR
			acc = system_bus ^ tmp;
			break;
		case 0x07:
			//CMP
			break;
	}
}
