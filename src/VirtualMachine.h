#pragma once

#include <vector>
#include <array>

namespace vm
{
    using MemType = int;
    enum class OpCode
    {
        PUSH,
        PUSH_VAL,
        POP,
        GET,
        DUP,
        SWAP,

        SET_REG,

        ADD,
        SUB,
        MUL,
        DIV,

        ADD_VAL,
        SUB_VAL,
        MUL_VAL,
        DIV_VAL,

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

    using RegisterIndex = char;
    static constexpr RegisterIndex REGISTER_COUNT = 8;

    struct Code
    {
        OpCode opCode;
        MemType operand = 0;
        RegisterIndex registerIndex;
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
    void executeCode(OpCode opCode, MemType operand = 0);

    MemType& getRegister(const int index);

    MemType popStack();
    MemType& getStack();
    MemType& pushStack(MemType value);

    std::vector<MemType> stack;
    std::vector<MemType> callstack;
    std::array<MemType, REGISTER_COUNT> registers = {0};

    MemType currentAddress = 0;
    Program program;
};
