#pragma once

#include <string>
#include <vector>

#include "VirtualMachine.h"

class Mutator
{
public:
    struct OpCodeWeight
    {
        OpCode opCode;
        int weight;
    };
    static constexpr int codeSize{ 128 };
    static constexpr int totalWeight{ 100 };
    static const std::vector<Mutator::OpCodeWeight> weights;

    static void saveProgramToFile(const Program& program, const std::string& path);
    static void insert(const Code& code, Program& program);
    static void remove(Program& program);
    static void edit(Code& code);
    static void random(OpCode& opCode);

    static OpCode getRandomOpCode();

    static Program generateCode();
    static void mutate(Program& program);
};