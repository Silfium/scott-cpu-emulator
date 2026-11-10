#pragma once
#include <cstdint>
#include <array>


//--------------------------|
//instruction values, opcodes
#define LD   0
#define ST   1
#define DATA 2
#define JMPR 3
#define JMP  4
#define J    5
#define CLF  6
#define IO   7
#define ADD  8
#define SHR  9
#define SHL  10
#define NOT  11
#define AND  12
#define OR   13
#define XOR  14
#define CMP  15





inline uint8_t system_bus;

struct Reg {
	uint8_t value;
	void set();
	void enable();
};


enum flagType : uint8_t {CARRY_OUT=1, A_LARGER=2, EQUAL=4, ZERO=8};
struct flagReg {
	uint8_t value;
	void set(flagType flag);
};

struct CPU   {
	Reg r0, r1, r2, r3;
	std::array<Reg, 4> general_purpose={r0, r1, r2, r3};
	Reg acc;
	Reg tmp;
	Reg ir;
	Reg iar;
	flagReg flags;
	bool bus1;
	uint8_t stepper;

	void execute();
	void step_cycle();
	// decode 
	void decode_ir();
	uint8_t get_opcode();
	uint8_t get_ra();
	uint8_t get_rb();
	void alu(uint8_t op);
	// reset and setup
	void reset();
}; inline CPU cpu;


struct RAM {
	
	std::array<uint8_t, 256> ram256{};
	Reg mar;
	void enable();
	void set();
	
}; inline RAM ram;

//struct keyboard {}
//struct display {}
