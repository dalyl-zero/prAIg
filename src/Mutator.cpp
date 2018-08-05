//
// Created by Dalyl on 02/08/2018.
//

#include "Mutator.h"

#include <fstream>
#include <random>

std::random_device device;
std::default_random_engine generate(device());
std::uniform_int_distribution<int> randomPosition(0, Mutator::codeSize - 1);
std::uniform_int_distribution<int> randomOpCode(0, static_cast<int>(Mutator::OpCodeList.size() - 1));
std::uniform_int_distribution<int> randomOperand(0, Mutator::codeSize);

const std::vector<OpCode> Mutator::OpCodeList = {
    OpCode::PUSH,
    OpCode::POP,
    OpCode::DUP,
    OpCode::ADD,
    OpCode::SUB,
    OpCode::MUL,
    OpCode::DIV,
    OpCode::JMP,
    OpCode::JIZ,
    OpCode::JNZ,
    OpCode::JIP,
    OpCode::JIN,
    OpCode::PRINT,
    OpCode::PRINT_CHAR,
    OpCode::INPUT,
    OpCode::CALL,
    OpCode::RETURN,
    OpCode::END
};

const std::map<OpCode, std::string> Mutator::opCodeString = {
    {OpCode::PUSH, "PUSH"},
    {OpCode::POP, "POP"},
    {OpCode::DUP, "DUP"},
    {OpCode::ADD, "ADD"},
    {OpCode::SUB, "SUB"},
    {OpCode::MUL, "MUL"},
    {OpCode::DIV, "DIV"},
    {OpCode::JMP, "JMP"},
    {OpCode::JIZ, "JIZ"},
    {OpCode::JNZ, "JNZ"},
    {OpCode::JIP, "JIP"},
    {OpCode::JIN, "JIN"},
    {OpCode::PRINT, "PRINT"},
    {OpCode::PRINT_CHAR, "PRINT_CHAR"},
    {OpCode::INPUT, "INPUT"},
    {OpCode::CALL, "CALL"},
    {OpCode::RETURN, "RETURN"},
    {OpCode::END, "END"}
};

void Mutator::saveProgramToFile(const Program& program, const std::string& path)
{
    std::ofstream file(path);

    if (file.is_open()) {
        for (auto line : program)
        {
            const std::string& opCode{ opCodeString.at(line.opCode) };
            MemType operand{ line.operand };

            file << opCode << " " << operand << "\n";
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
    opCode = OpCodeList[randomOpCode(generate)];
}

Program& Mutator::generateCode()
{
    Program randomCode;

    for (int i{0}; i < codeSize; i++)
    {
        Code instruction{ OpCodeList[randomOpCode(generate)], randomOperand(generate) };
        randomCode.push_back(instruction);
    }

    saveProgramToFile(randomCode, "log.ai");

    return randomCode;
}