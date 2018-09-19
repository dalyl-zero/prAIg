#pragma once

#include <string>
#include <vector>
#include <random>

#include "VirtualMachine.h"

class Mutator
{
public:
	Mutator();

    struct OpCodeWeight
    {
        OpCode opCode;
        int weight;
    };
    using OpCodeWeights = std::vector<OpCodeWeight>;
    void setOpCodeWeights(const OpCodeWeights& weights);


    enum CodeMutation
    {
        INCREMENT_OPERAND,
        DECREMENT_OPERAND,
        INCREMENT_REGISTER,
        DECREMENT_REGISTER,
        NEW_OPCODE,
        NEW_OPERAND,
        NEW_REGISTER
    };

    struct CodeMutationWeight
    {
        CodeMutation mutation;
        int weight;
    };
    using CodeMutationWeights = std::vector<CodeMutationWeight>;

    void setCodeMutationWeights(const CodeMutationWeights& weights);

    void saveProgramToFile(const Program& program, const std::string& path);

    Program generateProgram(int programSize = 100);

    void mutate(Program& program);

    std::uniform_int_distribution<int> randomOperand;
    std::uniform_int_distribution<int> randomRegister;
    std::uniform_int_distribution<int> randomMutate;

private:    

    int totalOpCodeWeights = 0;
    OpCodeWeights opCodeWeights = {};

    int totalCodeMutationWeights = 0;
    CodeMutationWeights codeMutationWeights = {};

    void insert(const Code& code, Program& program);
    void remove(Program& program);
    void random(OpCode& opCode);

    OpCode getRandomOpCode();
    CodeMutation getRandomCodeMutation();

    void mutate(Code& code, CodeMutation mutation);
    
    std::default_random_engine randEngine;
};