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

    int totalOpCodeWeights = 0;
    OpCodeWeights opCodeWeights = {};
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

    int totalCodeMutationWeights = 0;
    CodeMutationWeights codeMutationWeights = {};
    void setCodeMutationWeights(const CodeMutationWeights& weights);

    void saveProgramToFile(const Program& program, const std::string& path);
    void insert(const Code& code, Program& program);
    void remove(Program& program);
    void random(OpCode& opCode);

    OpCode getRandomOpCode();
    CodeMutation getRandomCodeMutation();

    Program generateProgram(int programSize = 100);


    void mutate(Code& code, CodeMutation mutation);
    void mutate(Program& program);

	std::default_random_engine randEngine;
	std::uniform_int_distribution<int> randomOperand;
	std::uniform_int_distribution<int> randomRegister;
	std::uniform_int_distribution<int> randomMutate;
};