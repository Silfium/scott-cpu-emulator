#include <iostream>
#include <string>
#include <cstdint>
#include "../src/utils/components.h"
#include "../src/utils/utils.h"

#define SEPERATOR "|------------------------------------|\n"
#define ZERO "test 0:"
#define MAX "test max possible value :"
#define MIN "test min possible value :"
#define ARBITARY "test arbitary value :"
#define ALL_IN_FIELD "test all possible values in the concerned field :"


void test_get_rb();
void test_get_ra();
void test_alu();

int main() {
	test_get_rb();
	test_get_ra();
	return 0;
}

void test_get_rb() {

	std::cout << SEPERATOR;

	std::cout << "test get RB function:\n";
	std::cout << ZERO;
	cpu.ir.value = 0;
        (cpu.get_rb() != 0) ? std::cout << " No\n" << std::endl :  std::cout << " Yes\n";

	std::cout << MAX;
	cpu.ir.value = 0b1111'1111;
	(cpu.get_rb() != 3) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << ARBITARY;
	cpu.ir.value = 0b0110'0110;
	(cpu.get_rb() != 2) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << ALL_IN_FIELD;
	bool isWrong = false;
	for (uint8_t i = 0b0000'0001; i <= 0b0000'0011; i++) {
		cpu.ir.value = i;
		if (cpu.get_rb() == i & !isWrong) { isWrong = false; } else { isWrong = true; }
	}
	(isWrong) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n" << std::endl;
 
}

void test_get_ra() {
	std::cout << SEPERATOR;
	
	std::cout << "test get RA funstion :\n";
	std::cout << ZERO;
	cpu.ir.value = 0;
        (cpu.get_ra() != 0) ? std::cout << " No\n" << std::endl :  std::cout << " Yes\n";

	std::cout << MAX;
	cpu.ir.value = 0b1111'1111;
	(cpu.get_rb() != 3) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << ARBITARY;
	cpu.ir.value = 0b0110'0110;
	(cpu.get_ra() != 1) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << ALL_IN_FIELD;
	bool isWrong = false;
        for (uint8_t i = 0b0000'0100; i <= 0b0000'1100; i++) {
                cpu.ir.value = i;
                if (cpu.get_ra() == (i >> 2) & !isWrong) { isWrong = false; } else { isWrong = true; }
        }
        (isWrong) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n" << std::endl;
}

void test_alu() {}
