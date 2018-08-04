//
// Created by Dalyl on 02/08/2018.
//

#include "Mutator.h"

#include <fstream>
#include <random>

std::random_device device;
std::default_random_engine generate(device());
std::uniform_int_distribution<int> randomPosition(0, codeSize - 1);
std::uniform_int_distribution<int> randomOpCode(0, static_cast<int>(OpCodeList.size() - 1));
std::uniform_int_distribution<int> randomOperand(0, codeSize);

void logCode(const Program& program)
{
    std::ofstream logFile(filePath);

    if (logFile.is_open()) {
        for (auto line : program)
        {
            const std::string opCode{ opCodeString.at(line.opCode) };
            const MemType operand{ line.operand };

            logFile << opCode;
            logFile << " ";
            logFile << operand;
            logFile << "\n";
        }
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
}

void insert(const Code& code, Program& program)
{
    const MemType pos{ randomPosition(generate) };
    program.insert(program.begin() + pos, code);
}

void remove(Program& program)
{
    const MemType pos{ randomPosition(generate) };
    program.erase(program.begin() + pos);
}

void edit(MemType& operand)
{
    const MemType value{ randomOperand(generate) };
    operand = value;
}

void random(OpCode& opCode)
{
    const OpCode value{ OpCodeList[randomOpCode(generate)] };
    opCode = value;
}

Program generateCode()
{
    Program randomCode;

    for (int i{0}; i < codeSize; i++)
    {
        Code instruction{ OpCodeList[randomOpCode(generate)], randomOperand(generate) };
        randomCode.push_back(instruction);
    }

    logCode(randomCode);

    return randomCode;
}