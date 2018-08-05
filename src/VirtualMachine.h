#pragma once

#include <vector>

namespace vm
{
    using MemType = int;
    enum class OpCode
    {
        PUSH,
        POP,
        DUP,

        ADD,
        SUB,
        MUL,
        DIV,

        JMP,
        JIZ,
        JNZ,
        JIP,
        JIN,

        PRINT,
        PRINT_CHAR,
        INPUT,

        CALL,
        RETURN,

        END,
    };

    struct Code
    {
        OpCode opCode;
        MemType operand = 0;
    };

    using Program = std::vector<Code>;
}

using namespace vm;

class VirtualMachine 
{
public:
    void setProgram(const Program& program);
    void executeProgram();
    void executeProgram(const Program& program);

private:
    void executeCode(const Code& code);
    void executeCode(OpCode& opCode, MemType operand = 0);

    MemType popStack();

    std::vector<MemType> stack;
    MemType currentAddress = 0;
    Program program;
};
