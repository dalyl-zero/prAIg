#pragma once

#include <string>
#include <vector>
#include <map>

#include "VirtualMachine.h"

using Program = VirtualMachine::Program;
using MemType = VirtualMachine::MemType;
using OpCode = VirtualMachine::OpCode;
using Code = VirtualMachine::Code;

const std::vector<OpCode> OpCodeList {
    OpCode::PUSH,
    OpCode::POP,
    OpCode::DUP,
    OpCode::ADD,
    OpCode::SUB,
    OpCode::MUL,
    OpCode::DIV,
    OpCode::JMP,
    OpCode::JIZ,
    OpCode::JNZ,
    OpCode::JIP,
    OpCode::JIN,
    OpCode::PRINT,
    OpCode::PRINT_CHAR,
    OpCode::INPUT,
    OpCode::CALL,
    OpCode::RETURN,
    OpCode::END
};

const std::map<OpCode, std::string> opCodeString {
    {OpCode::PUSH, "PUSH"},
    {OpCode::POP, "POP"},
    {OpCode::DUP, "DUP"},
    {OpCode::ADD, "ADD"},
    {OpCode::SUB, "SUB"},
    {OpCode::MUL, "MUL"},
    {OpCode::DIV, "DIV"},
    {OpCode::JMP, "JMP"},
    {OpCode::JIZ, "JIZ"},
    {OpCode::JNZ, "JNZ"},
    {OpCode::JIP, "JIP"},
    {OpCode::JIN, "JIN"},
    {OpCode::PRINT, "PRINT"},
    {OpCode::PRINT_CHAR, "PRINT_CHAR"},
    {OpCode::INPUT, "INPUT"},
    {OpCode::CALL, "CALL"},
    {OpCode::RETURN, "RETURN"},
    {OpCode::END, "END"}
};

const std::string filePath("../log/test.ai");

constexpr int codeSize{ 128 };

void logCode(const Program& program);
void insert(const Code& code, Program& program);
void remove(const Program& program);
void edit(MemType& operand);
void random(OpCode& opCode);
Program generateCode();