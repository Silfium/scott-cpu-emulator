#include "assembler8bit.h"
#include <string> 

int main() {

	std::string source = 	"LD R0 R1 \ 
			      	\n ST R3 R2 \
			      	\n DATA R1 0 \
				\n JMPR R2 \
				\n JMP 255 \
				\n CLF \
				\n ADD R2 R2 \
				\n SHR R1 R0 \
				\n XOR R3 R1";
	assemble(source);

	return 0;
 }
