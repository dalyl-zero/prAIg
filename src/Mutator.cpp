//
// Created by Dalyl on 02/08/2018.
//

#include "Mutator.h"

#include <fstream>

Mutator::Mutator(): randEngine(std::random_device{}())
{
    randomMutate = std::uniform_int_distribution<int>{0, 700};
    randomOperand = std::uniform_int_distribution<int>{10, 122};
    randomRegister = std::uniform_int_distribution<int>{-1, -1};

    setOpCodeWeights(
    {
        {OpCode::PUSH, 100},
        {OpCode::PRINT_CHAR, 100},
    });

    setCodeMutationWeights(
    {
        {INCREMENT_OPERAND, 30},
        {DECREMENT_OPERAND, 30},
        {INCREMENT_REGISTER, 0},
        {DECREMENT_REGISTER, 0},
        {NEW_OPCODE, 2},
        {NEW_OPERAND, 2},
        {NEW_REGISTER, 0}
    });
}

void Mutator::setOpCodeWeights(const OpCodeWeights& weights)
{
    opCodeWeights = weights;

    totalOpCodeWeights = 0;
    for(const OpCodeWeight& weight : opCodeWeights)
    {
        totalOpCodeWeights += weight.weight;
    }
}

void Mutator::setCodeMutationWeights(const CodeMutationWeights& weights)
{
    codeMutationWeights = weights;

    totalCodeMutationWeights = 0;
    for(const CodeMutationWeight& weight : codeMutationWeights)
    {
        totalCodeMutationWeights += weight.weight;
    }
}

OpCode Mutator::getRandomOpCode()
{
    std::uniform_int_distribution<int> randomWeight(0, totalOpCodeWeights);

    int selected = randomWeight(randEngine);
    for (const OpCodeWeight& opCodeWeight : opCodeWeights)
    {
        selected -= opCodeWeight.weight;
        if (selected <= 0)
        {
            return opCodeWeight.opCode;
        }
    }

    return {};
}

Mutator::CodeMutation Mutator::getRandomCodeMutation()
{
    std::uniform_int_distribution<int> randomWeight(0, totalCodeMutationWeights);

    int selected = randomWeight(randEngine);
    for (const CodeMutationWeight& codeMutationWeight : codeMutationWeights)
    {
        selected -= codeMutationWeight.weight;
        if (selected <= 0)
        {
            return codeMutationWeight.mutation;
        }
    }

    return {};
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
    MemType pos{ randomPosition(randEngine) };
    program.insert(program.begin() + pos, code);
}

void Mutator::remove(Program& program)
{
    std::uniform_int_distribution<int> randomPosition(0, program.size() - 1);
    MemType pos{ randomPosition(randEngine) };
    program.erase(program.begin() + pos);
}

void Mutator::mutate(Code& code, CodeMutation mutation)
{
    if(mutation == INCREMENT_OPERAND)
    {
        code.operand++;
    }
    else if(mutation == DECREMENT_OPERAND)
    {
        code.operand--;
    }
    else if(mutation == INCREMENT_REGISTER)
    {
        code.registerIndex++;
    }
    else if(mutation == DECREMENT_REGISTER)
    {
        code.registerIndex--;
    }
    else if(mutation == NEW_OPCODE)
    {
        code.opCode = getRandomOpCode();
    }
    else if(mutation == NEW_OPERAND)
    {
        code.operand = randomOperand(randEngine);
    }
    else if(mutation == NEW_REGISTER)
    {
        code.registerIndex = randomRegister(randEngine);
    }
}

void Mutator::random(OpCode& opCode)
{
    opCode = getRandomOpCode();
}

Program Mutator::generateProgram(int programSize)
{
    Program program;

    for (int i{0}; i < programSize; i++)
    {
        Code instruction{ getRandomOpCode(), randomOperand(randEngine), randomRegister(randEngine)};
        program.push_back(instruction);
    }

    return program;
}

void Mutator::mutate(Program& program)
{
    for(Code& code: program)
    {
        if(randomMutate(randEngine) <= 10)
        {
            mutate(code, getRandomCodeMutation());
        }
    }

    if(randomMutate(randEngine) == 0)
    {
        remove(program);
    }

    if(randomMutate(randEngine) == 0)
    {
        Code instruction{getRandomOpCode(), randomOperand(randEngine), randomRegister(randEngine)};
        insert(instruction, program);
    }
}