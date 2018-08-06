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

void VirtualMachine::setInput(const std::string& input)
{
    this->input.str(input);
}

std::string VirtualMachine::getOutput() const
{
    return output.str();
}

MemType VirtualMachine::popStack()
{
    if (stack.empty())
    {
        throw std::logic_error("Stack Underflow Error");
    }

    MemType value = stack.back();
    stack.pop_back();

    return value;
}

MemType& VirtualMachine::getStack()
{
    if (stack.empty())
    {
        throw std::logic_error("Stack Underflow Error");
    }

    return stack.back();
}

MemType& VirtualMachine::pushStack(MemType value)
{
    stack.push_back(value);
    return stack.back();
}

MemType& VirtualMachine::getRegister(const RegisterIndex index)
{
    if (index < 0 || index >= REGISTER_COUNT)
    {
        throw std::logic_error("Register Index Out Of Bound");
    }

    return registers[index];
}

void VirtualMachine::executeCode(OpCode opCode, MemType operand, RegisterIndex registerIndex)
{
    executeCode({opCode, operand, registerIndex});
}

void VirtualMachine::executeCode(const Code& code)
{
    const OpCode& opCode = code.opCode;
    const MemType& operand = code.operand;
    const RegisterIndex& registerIndex = code.registerIndex;

    if(opCode == OpCode::PUSH)
    {   
        if(registerIndex >= 0)
        {
            stack.push_back(getRegister(registerIndex));
        }
        else
        {
            stack.push_back(operand);
        }
        
    }
    else if(opCode == OpCode::POP)
    {
        if(registerIndex >= 0)
        {
            getRegister(registerIndex) = popStack();
        }
        else
        {
            popStack();
        }
    }
    else if(opCode == OpCode::POP)
    {
        if(registerIndex >= 0)
        {
            getRegister(registerIndex) = getStack();
        }
        else
        {
            getStack();
        }
    }
    else if(opCode == OpCode::DUP)
    {
        stack.push_back(getStack());
    }
    else if(opCode == OpCode::SWAP)
    {
        if(registerIndex < 0)
        {
            if (stack.size() < 2)
            {
                throw std::logic_error("Stack Underflow Error");
            }

            std::swap(stack[stack.size() - 1], stack[stack.size() - 2]);
        }
        else
        {
            std::swap(getStack(), getRegister(registerIndex));
        }
    }
    else if(opCode == OpCode::SET_REG)
    {
        getRegister(registerIndex) = operand;
    }
    else if(opCode == OpCode::ADD)
    {
        if(registerIndex < 0)
        {
            getStack() += operand;
        }
        else
        {
            getStack() += getRegister(registerIndex);
        }
    }
    else if(opCode == OpCode::SUB)
    {
        if(registerIndex < 0)
        {
            getStack() -= operand;
        }
        else
        {
            getStack() -= getRegister(registerIndex);
        }
    }
    else if(opCode == OpCode::MUL)
    {
        if(registerIndex < 0)
        {
            getStack() *= operand;
        }
        else
        {
            getStack() *= getRegister(registerIndex);
        }
    }
    else if(opCode == OpCode::DIV)
    {
        const MemType& divisor = (registerIndex < 0 ? operand : getRegister(registerIndex));

        if (divisor == 0)
        {
            throw std::logic_error("Math Error: Division by zero");
        }

        getStack() /= divisor;
    }
    else if(opCode == OpCode::PRINT)
    {
        const MemType& value = (registerIndex < 0 ? popStack() : getRegister(registerIndex));
        output << value;// << std::endl;
    }
    else if(opCode == OpCode::PRINT_CHAR)
    {
        const MemType& value = (registerIndex < 0 ? popStack() : getRegister(registerIndex));
        output << static_cast<char>(value);// << std::endl;
    }
    else if(opCode == OpCode::INPUT)
    {
        if(input.str().empty())
        {
            throw std::logic_error("Empty Input");
        }

        MemType& value = (registerIndex < 0 ? pushStack(0) : getRegister(registerIndex));
        input >> value;
    }
    else if(opCode == OpCode::JMP)
    {
        currentAddress += code.operand;
        currentAddress--; //because we increment at the end

        if (currentAddress < 0 || currentAddress > static_cast<MemType>(program.size()))
        {
            throw std::logic_error("Execution address out of bound");
        }

    }
    else if(opCode == OpCode::JIZ)
    {
        MemType value = (registerIndex < 0 ? getStack() : getRegister(registerIndex));
        if (value == 0)
        {
            executeCode(OpCode::JMP, code.operand);
        }
    }
    else if(opCode == OpCode::JNZ)
    {
        MemType value = (registerIndex < 0 ? getStack() : getRegister(registerIndex));
        if (value != 0)
        {
            executeCode(OpCode::JMP, code.operand);
        }
    }
    else if(opCode == OpCode::JIP)
    {
        MemType value = (registerIndex < 0 ? getStack() : getRegister(registerIndex));
        if (value > 0)
        {
            executeCode(OpCode::JMP, operand);
        }
    }
    else if(opCode == OpCode::JIN)
    {
        MemType value = (registerIndex < 0 ? getStack() : getRegister(registerIndex));
        if (value < 0)
        {
            executeCode(OpCode::JMP, operand);
        }
    }
    else if(opCode == OpCode::CALL)
    {
        callstack.push_back(currentAddress);
        executeCode(OpCode::JMP, operand);
    }
    else if(opCode == OpCode::RETURN)
    {
        if (callstack.empty())
        {
            throw std::logic_error("Callstack Underflow Error");
        }

        const MemType address = callstack.back();
        callstack.pop_back();

        currentAddress = address;
    }
    else if(opCode == OpCode::END)
    {
        currentAddress = static_cast<MemType>(program.size());
    }
    else 
    {
        throw std::logic_error("Unhandled OpCode");
    }
}


void VirtualMachine::executeProgram() 
{
    currentAddress = 0;
    registers = {0};
    callstack.clear();

    output.str("");

    int instructionCount = 0;

    while (currentAddress < static_cast<MemType>(program.size())) 
    {
        executeCode(program[currentAddress]);
        currentAddress++;

        if(instructionCount++ > 1000)
        {
            throw std::logic_error("Infinite execution");
        }
    }
}

void VirtualMachine::executeProgram(const Program& program) 
{
    setProgram(program);
    executeProgram();
}