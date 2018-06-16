
#include <cstring>

#include "SynacorDisassembler.h"

void SynacorDisassembler::disassemble(const char *in, const char *out) 
{
	std::ifstream program(in, std::ios::binary | std::ios::ate);
	if (!program)
	{
		std::cerr << "Error loading program" << std::endl;
		return;
	}

	writer.open(out, std::ios::out);

	if (!writer)
	{
		std::cerr << "Couldn't open " << out << " for writing" << std::endl;
		return;
	}

	auto progSize = program.tellg();
	std::vector<unsigned char> buffer(progSize);
	program.seekg(0, std::ios::beg);
	program.read((char*)&buffer[0], progSize);
	memory.resize((progSize / 2) + 1);
	std::memcpy(&memory[0], &buffer[0], progSize);

	doDisassembly();

	std::cout << in << " successfully disassembled to " << out << std::endl;
}

void SynacorDisassembler::doDisassembly()
{
	char buffer[0x100] = { 0 };

	for (std::size_t i = 0; i < memory.size();)
	{
		memset(buffer, 0, sizeof(buffer));
		std::size_t pos = 0;

		if (IS_VALID_OPCODE(memory[i]))
		{
			uint16 op = memory[i++];
			auto opInfo = opcodes[op];

			pos = snprintf(buffer, sizeof(buffer), "[0x%04lux] %-5s", i - 1, opInfo.name);
			for (std::size_t j = 0; j < opInfo.nargs; j++)
			{
				if (IS_REG(memory[i]))
					pos += snprintf(buffer + pos, sizeof(buffer) - pos,
					(j ? ", r%d" : " r%d"), memory[i] - (uint16)0x8000);
				else
					pos += snprintf(buffer + pos, sizeof(buffer) - pos,
					(j ? ", 0x%04x" : " 0x%04x"), memory[i]);
				i++;
			}
			writer << buffer << std::endl;
		}
		else i++;
	}
	writer.close();
}
