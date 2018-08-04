#include <iostream>

//#include "VirtualMachine.h"
//
//using OpCode = VirtualMachine::OpCode;
//using Code = VirtualMachine::Code;

#include "Mutator.h"

int main() {
	VirtualMachine vm;

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

    Program test{ generateCode() };

	vm.executeProgram(test); // Lord, have mercy.
}