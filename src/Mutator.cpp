//
// Created by Dalyl on 02/08/2018.
//

#include "Mutator.h"

#include <fstream>
#include <random>

std::random_device device;
std::default_random_engine generate(device());
std::uniform_int_distribution<int> randomPosition(0, Mutator::codeSize - 1);
std::uniform_int_distribution<int> randomOpCode(0, static_cast<int>(OpCode::OPCODE_COUNT) - 1);
std::uniform_int_distribution<int> randomOperand(0, Mutator::codeSize);


OpCode Mutator::getRandomOpCode()
{
    return static_cast<OpCode>(randomOpCode(generate));
}

void Mutator::saveProgramToFile(const Program& program, const std::string& path)
{
    std::ofstream file(path);

    if (file.is_open()) 
    {
        for (const Code& line : program)
        {
            file << to_string(line.opCode) << " " << line.operand << "\n";
        }
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + path);
    }
}

void Mutator::insert(const Code& code, Program& program)
{
    MemType pos{ randomPosition(generate) };
    program.insert(program.begin() + pos, code);
}

void Mutator::remove(Program& program)
{
    MemType pos{ randomPosition(generate) };
    program.erase(program.begin() + pos);
}

void Mutator::edit(MemType& operand)
{
    operand = randomOperand(generate);
}

void Mutator::random(OpCode& opCode)
{
    opCode = getRandomOpCode();
}

Program Mutator::generateCode()
{
    Program randomCode;

    for (int i{0}; i < codeSize; i++)
    {
        Code instruction{ getRandomOpCode(), randomOperand(generate) };
        randomCode.push_back(instruction);
    }

    saveProgramToFile(randomCode, "log.ai");

    return randomCode;
}