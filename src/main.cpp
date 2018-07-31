#include <iostream>

#include "VirtualMachine.h"

using OpCode = VirtualMachine::OpCode;

int main() 
{
	VirtualMachine vm;

	vm.executeProgram(
	{
		{OpCode::PUSH, 1},
		{OpCode::PRINT},
	});

	std::cout << "printed: 1" << std::endl << std::endl;

	vm.executeProgram(
	{
		{OpCode::PUSH, 1},
		{OpCode::PUSH, 2},
		{OpCode::ADD},
		{OpCode::PRINT},
	});

	std::cout << "printed: 3" << std::endl << std::endl;

	vm.executeProgram(
	{
		{OpCode::PUSH, 1},
		{OpCode::PUSH, 2},
		{OpCode::PUSH, 3},
		{OpCode::POP},
		{OpCode::PRINT},
		{OpCode::PRINT},
	});

	std::cout << "printed: 2, 1" << std::endl << std::endl;

	vm.executeProgram(
	{
		{OpCode::PUSH, 1},
		{OpCode::PUSH, 2},
		{OpCode::PUSH, 3},
		{OpCode::JMP, 3},
		{OpCode::POP},
		{OpCode::PRINT},
		{OpCode::PRINT},
	});

	std::cout << "printed: 3" << std::endl << std::endl;

	vm.executeProgram(
	{
		{OpCode::JMP, 2},
		{OpCode::END},
		{OpCode::PUSH, 2},
		{OpCode::PUSH, 3},
		{OpCode::PUSH, 3},
		{OpCode::JIZ, -4},
		{OpCode::PRINT},
		{OpCode::SUB},
		{OpCode::JIZ, -7},
		{OpCode::PRINT},
	});

	std::cout << "printed: 3" << std::endl << std::endl;

	vm.executeProgram(
	{
		{OpCode::PUSH, 2},
		{OpCode::JNZ, 2},
		{OpCode::END},
		{OpCode::PUSH, 2},
		{OpCode::PRINT},
	});

	std::cout << "printed: 2" << std::endl << std::endl;

    return 0;
}