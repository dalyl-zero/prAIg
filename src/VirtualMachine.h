#pragma once

#include <vector>

class VirtualMachine 
{
public:
    using MemType = int;
    enum class OpCode
    {
        PUSH,
        POP,

        ADD,
        SUB,
        MUL,
        DIV,

        JMP,
        JIZ,
        JNZ,

        PRINT,
        INPUT,

        END,
    };

    struct Code
    {
        OpCode opCode;
        MemType operand = 0;
    };

    using Program = std::vector<Code>;

    void setProgram(const Program& program);
    void executeProgram();
    void executeProgram(const Program& program);

private:
    void executeCode(const Code& code);
    void executeCode(OpCode opCode, MemType operand = 0);


    MemType popStack();

    std::vector<MemType> stack;
    MemType currentAddress = 0;
    Program program;
};
