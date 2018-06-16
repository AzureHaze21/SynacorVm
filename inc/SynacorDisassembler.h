#ifndef _SYNACORDISASM_H_
#define _SYNACORDISASM_H_

#include "constants.h"

#include <fstream>
#include <vector>
#include <iostream>

using uint16 = unsigned short;

class SynacorDisassembler
{
private:

	std::ofstream writer;
	std::vector<uint16> memory;

	struct OpcodeInfo
	{
		const char *name;
		std::size_t nargs;
	};

	const OpcodeInfo opcodes[22] =
	{
		{ "HALT",	0 },
		{ "SET",	2 },
		{ "PUSH",	1 },
		{ "POP",	1 },
		{ "EQ",		3 },
		{ "GT",		3 },
		{ "JMP",	1 },
		{ "JT",		2 },
		{ "JF",		2 },
		{ "ADD",	3 },
		{ "MULT",	3 },
		{ "MOD",	3 },
		{ "AND",	3 },
		{ "OR",		3 },
		{ "NOT",	2 },
		{ "RMEM",	2 },
		{ "WMEM",	2 },
		{ "CALL",	1 },
		{ "RET",	0 },
		{ "OUT",	1 },
		{ "IN",		1 },
		{ "NOP",	0 },
	};

private:
	void doDisassembly();

public:
	void disassemble(const char *in, const char *out);
};

#endif
