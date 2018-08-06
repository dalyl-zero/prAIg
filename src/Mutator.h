#pragma once

#include <string>
#include <vector>
#include <map>

#include "VirtualMachine.h"

class Mutator
{
public:
    static constexpr int codeSize{ 128 };

    static void saveProgramToFile(const Program& program, const std::string& path);
    static void insert(const Code& code, Program& program);
    static void remove(Program& program);
    static void edit(Code& code);
    static void random(OpCode& opCode);

    static OpCode getRandomOpCode();

    static Program generateCode();
    static void mutate(Program& program);
};