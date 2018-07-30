//
// Created by Dalyl on 30/07/2018.
//

#include "VirtualMachine.h"

#include <exception>
#include <stdexcept>
#include <iostream>

VirtualMachine::VirtualMachine() : executionAddress(0) {
}

void VirtualMachine::setCode(VirtualMachine::OpCodes opCode, VirtualMachine::MemType operand) {
    code.emplace_back(std::make_pair(opCode, operand));
}

void VirtualMachine::execute() {
    while (executionAddress < code.size()) {
        auto currentLine{ code[executionAddress] };
        switch (currentLine.first) {
            case OpCodes::PUSH: {
                stack.push_back(currentLine.second);
                break;
            }
            case OpCodes::POP: {
                if (stack.empty())
                    throw std::logic_error("Stack Underflow Error");
                stack.pop_back();
                break;
            }
            case OpCodes::ADD: {
                MemType add{stack.back()};
                setCode(OpCodes::POP);
                add += stack.back();
                setCode(OpCodes::POP);
                setCode(OpCodes::PUSH, add);
                break;
            }
            case OpCodes::SUB: {
                MemType sub{stack.back()};
                setCode(OpCodes::POP);
                sub -= stack.back();
                setCode(OpCodes::POP);
                setCode(OpCodes::PUSH, sub);
                break;
            }
            case OpCodes::MUL: {
                MemType mul{stack.back()};
                setCode(OpCodes::POP);
                mul *= stack.back();
                setCode(OpCodes::POP);
                setCode(OpCodes::PUSH, mul);
                break;
            }
            case OpCodes::DIV: {
                MemType div{stack.back()};
                setCode(OpCodes::POP);
                if (stack.back() == 0)
                    throw std::logic_error("Math Error: Division by zero");
                div /= stack.back();
                setCode(OpCodes::POP);
                setCode(OpCodes::PUSH, div);
                break;
            }
            case OpCodes::PRINT: {
                std::cout << stack.back() << std::endl;
                break;
            }
            case OpCodes::INPUT: {
                MemType input;
                std::cin >> input;
                setCode(OpCodes::PUSH, input);
                break;
            }
            case OpCodes::JUMP: {
                if (currentLine.second > 0)
                    executionAddress += currentLine.second + 1;
                if (currentLine.second < 0)
                    executionAddress += currentLine.second;
                if (executionAddress < 0 || executionAddress > code.size())
                    throw std::logic_error("Stack Overflow Error");
                break;
            }
        }
        if (currentLine.first != OpCodes::JUMP)
            executionAddress++;
    }
}