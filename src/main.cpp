#include <iostream>

#include "Mutator.h"

int main()
{
//	std::vector<Code> minmax{
//            {OpCode::JMP, 32},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'h'},
//            {OpCode::PUSH, 'g'},
//            {OpCode::PUSH, 'i'},
//            {OpCode::PUSH, 'H'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::JMP, 15},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'w'},
//            {OpCode::PUSH, 'o'},
//            {OpCode::PUSH, 'L'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::PUSH, ':'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'b'},
//            {OpCode::PUSH, 'm'},
//            {OpCode::PUSH, 'u'},
//            {OpCode::PUSH, 'n'},
//            {OpCode::PUSH, ' '},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'h'},
//            {OpCode::PUSH, 't'},
//            {OpCode::PUSH, ' '},
//            {OpCode::PUSH, 's'},
//            {OpCode::PUSH, 's'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'u'},
//            {OpCode::PUSH, 'G'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::PUSH, 29}, // The random number ! Please make it random :(
//            {OpCode::INPUT},
//            {OpCode::SUB},
//            {OpCode::DUP},
//
//            {OpCode::JIP, -54},
//            {OpCode::JIN, -72},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 't'},
//            {OpCode::PUSH, 'c'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'o'},
//            {OpCode::PUSH, 'C'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//	};
//
//	vm.executeProgram(minmax);

	std::vector<Code> fibonacci
	{
		{OpCode::PUSH, 0},
		{OpCode::PUSH, 1},

		{OpCode::PUSH, 45},
		{OpCode::POP, 0, 2},

		{OpCode::POP, 0, 0},
		{OpCode::POP, 0, 1},

		{OpCode::PUSH, 0},

		{OpCode::ADD, 0, 0},
		{OpCode::ADD, 0, 1},

		{OpCode::DUP, 0},
		{OpCode::PRINT, 0},

		{OpCode::SWAP, 0, 0},
		{OpCode::POP, 0, 1},

		{OpCode::PUSH, 0, 1},
		{OpCode::PUSH, 0, 0},

		{OpCode::PUSH, 0, 2},
		{OpCode::SUB, 1},

		{OpCode::JIP, -14}
	};

	VirtualMachine vm;
	vm.executeProgram(fibonacci);

	while(true)
	{
		try
		{
			vm.executeProgram(Mutator::generateCode()); // Lord, have mercy.
		}
		catch(std::logic_error exception)
		{
			std::cout << exception.what() << std::endl;
		}

		std::cout << "Next program" << std::endl;
	}

	return 0;
}