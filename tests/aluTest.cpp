#include <iostream>
#include <cassert>
#include <cstdint>
#include "../src/utils/components.h"


CPU cpu_test;


void test_cpu();
void test_alu();
void test_operation_alu(uint8_t operation);

int main() {
	test_alu();
	return 0;
}


void test_alu()   {
	for (uint8_t op = 0x00; op <= 0x07; op++) {
		test_operation_alu(op);
	}
}

void test_operation_alu(uint8_t operation) {
	std::cout << static_cast<int>(operation) << "\n";

	cpu_test::alu(operation);
}
