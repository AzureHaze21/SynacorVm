#ifndef _SYNACORVM_H_
#define _SYNACORVM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "constants.h"

using uint16 = unsigned short;

class SynacorVm
{
private:
	
	uint16 registers[8]{ 0 };
	std::size_t ip = 0;
	int sp = -1;
	short stack[STACK_MAX]{ 0 };
	std::vector<uint16> memory;
	bool isRunning{ true };

private:

	uint16 getMemory(uint16 val) {
		return IS_REG(val) ? registers[val - (uint16)0x8000] : val;
	}

	void setRegValue(uint16 a, uint16 val) {
		if (IS_REG(a) && IS_VALID_VALUE(val)) registers[a - (uint16)0x8000] = val;
	}

public:

	SynacorVm() {}
	virtual ~SynacorVm() { stop(); }
	
	void stop() noexcept {
		isRunning = false;
		std::cout << "Shutting down virtual machine" << std::endl;
	}

	void reset() {
		std::memset(registers, 0, sizeof(registers));
		memory.clear();
		ip = 0;
		sp = -1;
	}

       	bool load(const char *path)
	{
		reset();

		std::ifstream program(path, std::ios::binary | std::ios::ate);
		if (!program) {
			std::cerr << "Error loading program" << std::endl;
			return false;
		}

		auto binSize = program.tellg();
		std::vector<unsigned char> buffer(binSize);
		program.seekg(0, std::ios::beg);
		program.read((char*)&buffer[0], binSize);
		memory.resize((binSize / 2) + 1);
		std::memcpy(&memory[0], &buffer[0], binSize);
		
		return true;
	}

	bool load(std::vector<uint16>&& program)
	{
		reset();
		std::swap(program, memory);

		return true;
	}
	
private:

	void HALT();
	void SET();
	void PUSH();
	void POP();
	void EQ();
	void GT();
	void JMP();
	void JT();
	void JF();
	void ADD();
	void MULT();
	void MOD();
	void AND();
	void OR();
	void NOT();
	void RMEM();
	void WMEM();
	void CALL();
	void RET();
	void OUT();
	void IN();
	void NOOP();
		
        void (SynacorVm::*jmpTable[OPCODE_COUNT])(void) =
	{
		&SynacorVm::HALT,
		&SynacorVm::SET,
		&SynacorVm::PUSH,
		&SynacorVm::POP,
		&SynacorVm::EQ,
		&SynacorVm::GT,
		&SynacorVm::JMP,
		&SynacorVm::JT,
		&SynacorVm::JF,
		&SynacorVm::ADD,
		&SynacorVm::MULT,
		&SynacorVm::MOD,
		&SynacorVm::AND,
		&SynacorVm::OR,
		&SynacorVm::NOT,
		&SynacorVm::RMEM,
		&SynacorVm::WMEM,
		&SynacorVm::CALL,
		&SynacorVm::RET,
		&SynacorVm::OUT,
		&SynacorVm::IN,
		&SynacorVm::NOOP
	};
};

#endif
