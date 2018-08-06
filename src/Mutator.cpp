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
std::uniform_int_distribution<int> randomRegister(0, 2);

std::uniform_int_distribution<int> randomMutate(0, 6);

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
    std::uniform_int_distribution<int> randomPosition(0, program.size() - 1);
    MemType pos{ randomPosition(generate) };
    program.insert(program.begin() + pos, code);
}

void Mutator::remove(Program& program)
{
    std::uniform_int_distribution<int> randomPosition(0, program.size() - 1);
    MemType pos{ randomPosition(generate) };
    program.erase(program.begin() + pos);
}

void Mutator::edit(Code& code)
{
    int mutateValue = randomMutate(generate);
    if(mutateValue == 0)
    {
        code.operand++;
    }
    else if(mutateValue == 1)
    {
        code.operand--;
    }
    else if(mutateValue == 2)
    {
        code.registerIndex++;
    }
    else if(mutateValue == 3)
    {
        code.registerIndex--;
    }
    else if(mutateValue == 4)
    {
        code.opCode = getRandomOpCode();
    }
    else if(mutateValue == 5)
    {
        code.operand = randomOperand(generate);
    }
    else if(mutateValue == 6)
    {
        code.registerIndex = randomRegister(generate);
    }
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
        Code instruction{ getRandomOpCode(), randomOperand(generate), randomRegister(generate)};
        randomCode.push_back(instruction);
    }

    saveProgramToFile(randomCode, "log.ai");

    return randomCode;
}

void Mutator::mutate(Program& program)
{
    for(Code& code: program)
    {
        if(randomMutate(generate))
        {
            edit(code);
        }
    }

    if(randomMutate(generate) == 0)
    {
        remove(program);
    }

    if(randomMutate(generate) == 0)
    {
        Code instruction{getRandomOpCode(), randomOperand(generate), randomRegister(generate)};
        insert(instruction, program);
    }
}