#pragma once
#include <cstdint>
#include <array>


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

	void step_cycle();
	// decode 
	void decode_ir();
	void get_opcode();
	void get_ra();
	void get_rb();
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
