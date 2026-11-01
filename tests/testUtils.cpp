#include <iostream>
#include <cassert>
#include <cstdint>
#include "../src/utils/utils.h"

//parsing ir
void test_get_opcode();
void test_get_ra_rb();

//utils for test
void test_print_binary();


//-------------------------------------------------------|
//-------------------------------------------------------|
int main() {
	test_get_ra_rb();
	return 0;
}
//-------------------------------------------------------|
//-------------------------------------------------------|

//--------------------------------------------------------|
//parsing ir
void test_get_opcode()  {
	for (uint8_t i = 0; i <= 15; i++) {
		cpu.ir.value = i << 4;
		print_binary(i << 4);
		std::cout << "  :  " << static_cast<int>(i);
		std::cout << "\n";
		if (get_opcode() != i) {
			std::cout << "issue here" << "\n";
		}
	}
}
void test_get_ra_rb() {
	for (uint8_t i = 0; i <= 15; i++) {
		cpu.ir.value = i;
		print_binary(i);
		std::cout << "  :  " << "RA: " << static_cast<int>(get_ra()) << "  RB: " << static_cast<int>(get_rb()) << "\n";
	}
}



// -------------------------------------------------------|
// utils for test
void test_print_binary() {
	for (uint8_t i = 0; i <= 255; i++) {
		std::cout << "dec : " << i << " binary : ";
		print_binary(i);
		std::cout << "\n";
	}
}
