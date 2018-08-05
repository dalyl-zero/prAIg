#pragma once

#include <string>
#include <vector>
#include <map>

#include "VirtualMachine.h"

class Mutator
{
public:
    static const std::vector<OpCode> OpCodeList;
    static const std::map<OpCode, std::string> opCodeString;
    static constexpr int codeSize{ 128 };

    static void saveProgramToFile(const Program& program, const std::string& path);
    static void insert(const Code& code, Program& program);
    static void remove(Program& program);
    static void edit(MemType& operand);
    static void random(OpCode& opCode);
    static Program generateCode();
};