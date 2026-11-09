#include "assembler8bit.h"
#include <string> 

int main() {

	std::string source = "ADD R1 R3  \n ADD R2 R2";
	assemble(source);

	return 0;
 }
