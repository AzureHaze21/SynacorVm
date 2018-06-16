#include <iostream>

#include "SynacorVm.h"
#include "SynacorDisassembler.h"

int usage()
{
	std::cerr
		<< "Usage: ./synacorvm <option> file"
		<< std::endl
		<< "\t-d src <dst> (disassemble binary, default to out.s)"
		<< std::endl;

	return 1;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return usage();
	if (!strcmp(argv[1], "-h"))
		return usage();
	if (argc == 2) {
		SynacorVm vm;
		if (vm.load(argv[1])) vm.start();
		else std::cerr << "Failed to run " << argv[1] << std::endl;
	}
	else if (argc > 2 && !strcmp(argv[1], "-d")) {
		SynacorDisassembler disasm;
		disasm.disassemble(argv[2], argc == 3 ? "out.s" : argv[3]);
	}
}
