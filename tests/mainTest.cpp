#include <iostream>
#include <string> 	
#include <cstdint> 	
#include "../src/utils/components.h" 	
#include "../src/utils/utils.h" 	


void test_get_rb();

int main() {
	test_get_rb();
	return 0;
}

void test_get_rb() {

	std::cout << "|-----------------------------------|\n";

	std::cout << "test get RB function:\ntest 0:";
	cpu.ir.value = 0;
        (cpu.get_rb() != 0) ? std::cout << " No\n" << std::endl :  std::cout << " Yes\n";

	std::cout << "test max possible value 255:";
	cpu.ir.value = 0b1111'1111;
	(cpu.get_rb() != 3) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << "test arbitrary value:";
	cpu.ir.value = 0b0110'0110;
	(cpu.get_rb() != 2) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n";

	std::cout << "test all possible values in the concerned field:";
	bool isWrong;
	for (uint8_t i = 0b0000'0001; i <= 0b0000'0011; i++) {
		cpu.ir.value = i;
		if (cpu.get_rb() == i & !isWrong) { isWrong = false; }
	}
	(isWrong) ? std::cout << " No\n" << std::endl : std::cout << " Yes\n" << std::endl;
 
}
