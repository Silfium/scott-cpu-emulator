#pragma once
#include <cstdint>
#include <array>


inline uint8_t system_bus;

struct CPU   {
	uint8_t r0, r1, r2, r3;
	uint8_t acc;
	uint8_t tmp;
	uint8_t ir;
	uint8_t iar;
	uint8_t flags;

	void alu(uint8_t op);
	void control_section();
};

struct RAM {
	std::array<uint8_t, 256> ram{};
	uint8_t mar;
};

//struct keyboard {}
//struct display {}
