//
// Created by Dalyl on 30/07/2018.
//

#include "VirtualMachine.h"

#include <exception>
#include <stdexcept>
#include <iostream>


void VirtualMachine::setProgram(const Program& program)
{
    this->program = program;
}

VirtualMachine::MemType VirtualMachine::popStack()
{
    if (stack.empty())
    {
        throw std::logic_error("Stack Underflow Error");
    }

    MemType value = stack.back();
    stack.pop_back();

    return value;
}

void VirtualMachine::executeCode(OpCode opCode, MemType operand)
{
    executeCode({opCode, operand});
}

void VirtualMachine::executeCode(const Code& code)
{
    switch (code.opCode)
    {
        case OpCode::PUSH: 
        {
            stack.push_back(code.operand);
            break;
        }
        case OpCode::POP: 
        {
            popStack();
            break;
        }
        case OpCode::DUP:
        {

            executeCode(OpCode::PUSH, stack.back());
            break;
        }
        case OpCode::ADD:
        {
            MemType value = popStack();
            value += popStack();
            executeCode(OpCode::PUSH, value);
            break;
        }
        case OpCode::SUB: 
        {
            MemType value = popStack();
            value -= popStack();
            executeCode(OpCode::PUSH, value);
            break;
        }
        case OpCode::MUL: 
        {
            MemType value = popStack();
            value *= popStack();
            executeCode(OpCode::PUSH, value);
            break;
        }
        case OpCode::DIV: 
        {
            const MemType value = popStack();
            const MemType divider = popStack();

            if (divider == 0)
            {
                throw std::logic_error("Math Error: Division by zero");
            }

            executeCode(OpCode::PUSH, value / divider);
            break;
        }
        case OpCode::PRINT: 
        {
            std::cout << popStack() << std::endl;
            break;
        }
        case OpCode::PRINT_CHAR:
        {
            std::cout << static_cast<char>(popStack()) << std::endl;
            break;
        }
        case OpCode::INPUT: 
        {
            MemType input;
            std::cin >> input;
            executeCode(OpCode::PUSH, input);
            break;
        }
        case OpCode::JMP: 
        {
            currentAddress += code.operand;
            currentAddress--; //because we increment at the end

            if (currentAddress < 0 || currentAddress > static_cast<MemType>(program.size()))
            {
                throw std::logic_error("Execution address out of bound");
            }

            break;
        }
        case OpCode::JIZ: 
        {
            const MemType value = popStack();
            if (value == 0)
            {
                executeCode(OpCode::JMP, code.operand);
            }
            break;
        }
        case OpCode::JNZ: 
        {
            const MemType value = popStack();
            if (value != 0)
            {
                executeCode(OpCode::JMP, code.operand);
            }
            break;
        }
        case OpCode::JIP:
        {
            const MemType value = popStack();
            if (value > 0)
            {
                executeCode(OpCode::JMP, code.operand);
            }
            break;
        }
        case OpCode::JIN:
        {
            const MemType value = popStack();
            if (value < 0)
            {
                executeCode(OpCode::JMP, code.operand);
            }
            break;
        }
/*        case OpCode::CALL:
        {
            executeCode(OpCode::PUSH, currentAddress);
            executeCode(OpCode::JMP, code.operand);
            break;
        }
        case OpCode::RETURN:
        {
            const MemType value = popStack();
            currentAddress = value;
            break;
        }*/
        case OpCode::END: 
        {
            currentAddress = static_cast<MemType>(program.size());
            break;
        }
        default:
            break;
    }
}


void VirtualMachine::executeProgram() 
{
    currentAddress = 0;
    while (currentAddress < static_cast<MemType>(program.size())) 
    {
        executeCode(program[currentAddress]);
        currentAddress++;
    }
}

void VirtualMachine::executeProgram(const Program& program) 
{
    setProgram(program);
    executeProgram();
}