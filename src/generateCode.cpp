//
// Created by Dalyl on 02/08/2018.
//

#include "generateCode.h"

#include <fstream>
#include <random>

void logCode(const Program& program)
{
    std::ofstream logFile(filePath);

    if (logFile.is_open()) {
        for (int line{0}; line < program.size(); line++)
        {
            const std::string opCode{ opCodeString.at(program[line].opCode) };
            const MemType operand{ program[line].operand };

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

Program generateCode()
{
    std::random_device rand;
    std::default_random_engine generate(rand());

    std::uniform_int_distribution<int> randomOpcode(0, static_cast<int>(OpCodeList.size() - 1));
    std::uniform_int_distribution<int> randomOperand(0, codeSize);

    Program randomCode;

    for (int i{0}; i < codeSize; i++)
    {
        Code instruction{ OpCodeList[randomOpcode(generate)], randomOperand(generate) };
        randomCode.push_back(instruction);
    }

    logCode(randomCode);

    return randomCode;
}