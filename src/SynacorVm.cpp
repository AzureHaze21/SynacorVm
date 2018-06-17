#include "SynacorVm.h"

void SynacorVm::HALT()
{		
	stop();
}

void SynacorVm::SET()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	setRegValue(a, b);
}

void SynacorVm::PUSH()
{		
	uint16 a = memory[ip++];
	stack[++sp] = getMemory(a);
}

void SynacorVm::POP()
{		
	if (sp < 0) HALT();
	short a = memory[ip++];
	setRegValue(a, stack[sp]);
	stack[sp--] = 0;
}

void SynacorVm::EQ()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, b == c);
}

void SynacorVm::GT()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, b > c);
}

void SynacorVm::JMP()
{
	uint16 addr = getMemory(memory[ip]);
	ip = addr;
}

void SynacorVm::JT()
{
	uint16 a = getMemory(memory[ip++]);
	uint16 b = getMemory(memory[ip++]);
	if (a > 0) ip = b;
}

void SynacorVm::JF()
{
	uint16 a = getMemory(memory[ip++]);
	uint16 b = getMemory(memory[ip++]);
	if (!a) ip = b;
}
			
void SynacorVm::ADD()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, (b + c) % 0x8000);
}
	
void SynacorVm::MULT()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, (b * c) % (uint16)0x8000);
}

void SynacorVm::MOD()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, (b % c) % (uint16)0x8000);
}

void SynacorVm::AND()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, (b & c));
}

void SynacorVm::OR()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	uint16 c = getMemory(memory[ip++]);
	setRegValue(a, (b | c));	
}

void SynacorVm::NOT()
{		
	uint16 a = memory[ip++];
	uint16 b = getMemory(memory[ip++]);
	setRegValue(a, b ^ (uint16)0x7FFF);
}

void SynacorVm::RMEM()
{		
	uint16 a = memory[ip++];
	uint16 b = memory[getMemory(memory[ip++])];
	setRegValue(a, b);
}

void SynacorVm::WMEM()
{		
	uint16 a = getMemory(memory[ip++]);
	uint16 b = getMemory(memory[ip++]);
	memory[a] = b;
}

void SynacorVm::CALL()
{
	stack[++sp] = ip + 1;
	ip = getMemory(memory[ip]);
}

void SynacorVm::RET()
{
	if (sp < 0) HALT();
	uint16 a = stack[sp--];
	ip = a;
}

void SynacorVm::OUT()
{		
	uint16 a = getMemory(memory[ip++]);
	std::cout << static_cast<char>(a);
}

void SynacorVm::IN()
{	
	uint16 a = memory[ip++];
	char c = getchar();
	setRegValue(a, c);
}

void SynacorVm::NOOP()
{
		
}

void SynacorVm::start() {
	while (isRunning && ip < memory.size()) {
		uint16 op = memory[ip++];
		if (IS_VALID_OPCODE(op)) {
			(this->*jmpTable[op])();
		}
		else {
			printf("Invalid instruction 0x%x at address 0x%04lx\n", op, ip - 1);
			stop();
		}
	}
}
