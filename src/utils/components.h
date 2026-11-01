#pragma once
#include <cstdint>
#include <array>


inline uint8_t system_bus;

struct Reg {
	uint8_t value;
	void set();
	void enable();
};

enum flags : uint8_t {CARRY_OUT=0x01, A_LARGER=0x02, EQUAL=0x04, ZERO=0x08};
struct flagReg {
	uint8_t value;
	void set(flags flag);
};

struct CPU   {
	std::array<Reg, 4> general_purpose={r0, r1, r2, r3};
	Reg acc;
	Reg tmp;
	Reg ir;
	Reg iar;
	flagReg flagsReg;
	uint8_t stepper;

	void step_cycle();
	void alu(uint8_t op);
	void control_section();
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
