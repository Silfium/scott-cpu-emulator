#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>
#include "../src/utils/components.h"
#include "../src/utils/utils.h"

#define SEPERATOR "|------------------------------------|\n"


void test_get_rb();
void test_get_ra();
void test_get_opcode();
//void test_alu();

int main() {
	test_get_rb();
	test_get_ra();
	test_get_opcode();
	test_alu();
	return 0;
}

void test_get_rb() {

	std::cout << SEPERATOR << std::endl;
	std::cout << "test get RB function:\n" << std::endl;

	//zero
	cpu.ir.value = 0;
        assert(cpu.get_rb() == 0);

	//max 255
	cpu.ir.value = 0b1111'1111;
	assert(cpu.get_rb() == 3);

	//arbitrary
	cpu.ir.value = 0b0110'0110;
	assert(cpu.get_rb() == 2);

	//all values possible in the field concerned
	for (uint8_t i = 0b0000'0001; i <= 0b0000'0011; i++) {
		cpu.ir.value = i;
		assert(cpu.get_rb() == i);
	}

	std::cout << "all test passed\n" << std::endl;
 
}

void test_get_ra() {
	std::cout << SEPERATOR << std::endl;
	std::cout << "test get RA funstion :\n" << std::endl;

	//zero
	cpu.ir.value = 0;
        assert(cpu.get_ra() == 0);

	//max 255
	cpu.ir.value = 0b1111'1111;
	assert(cpu.get_rb() == 3);

	//arbitrary
	cpu.ir.value = 0b0110'0110;
	assert(cpu.get_ra() == 1);
	
	//all values possible in the field concerned
        for (uint8_t i = 0b0000'0100; i <= 0b0000'1100; i++) {
                cpu.ir.value = i;
                assert(cpu.get_ra() == (i >> 2));
        }
	std::cout << "all test passed\n" << std::endl;
}

void test_get_opcode() {
	std::cout << SEPERATOR << std::endl;
	std::cout << "test get opcode function :\n" << std::endl;
	
	//zero
	cpu.ir.value = 0;
        assert(cpu.get_opcode() == 0);

	//max 255
	cpu.ir.value = 0b1111'1111;
        assert(cpu.get_opcode() == 15);

	//arbitrary
	cpu.ir.value = 0b0110'0110;
        assert(cpu.get_opcode() == 6);
	
	//all values possible in the field concerned
        for (uint8_t i = 0b0000'0001; i <= 0b0000'1111; i++) {
                cpu.ir.value = i << 4;
		assert(cpu.get_opcode() == i);
	}
	std::cout << "all test passed\n" << std::endl;
}

void test_alu() {
	std::cout << SEPERATOR << std::endl;
	std::cout << "test the ALU func :\n" << std::endl;
	
	
}
