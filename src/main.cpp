#include "SynacorVm.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Usage: ./synacorvm [file]" << std::endl;
		return 1;
	}

	SynacorVm vm;
	
	if (vm.load(argv[1]))
		vm.start();
	else
		std::cerr << "Failed to load " << argv[1] << std::endl;
	
	return 0;
}
