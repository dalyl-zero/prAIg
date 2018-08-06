#pragma once

#include "Smartenum.hpp"

#include <vector>
#include <array>
#include <sstream>

namespace vm
{
    using MemType = int;
    smart_enum_class(OpCode,

        PUSH,
        POP,
        GET,
        DUP,
        SWAP,

        SET_REG,

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

        OPCODE_COUNT // Must always be last
    );

    using RegisterIndex = char;
    static constexpr RegisterIndex REGISTER_COUNT = 8;

    struct Code
    {
        OpCode opCode;
        MemType operand = 0;
        RegisterIndex registerIndex = -1;
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

    void setInput(const std::string& input);
    std::string getOutput() const;

private:
    void executeCode(const Code& code);
    void executeCode(OpCode opCode, MemType operand = 0, RegisterIndex registerIndex = -1);

    MemType& getRegister(const RegisterIndex index);

    MemType popStack();
    MemType& getStack();
    MemType& pushStack(MemType value);

    std::istringstream input;
    std::ostringstream output;

    std::vector<MemType> stack;
    std::vector<MemType> callstack;
    std::array<MemType, REGISTER_COUNT> registers = {0};

    MemType currentAddress = 0;
    Program program;
};
