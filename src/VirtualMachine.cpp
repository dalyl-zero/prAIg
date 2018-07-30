//
// Created by Dalyl on 30/07/2018.
//

#include "VirtualMachine.h"

#include <exception>
#include <stdexcept>
#include <iostream>
#include <cmath>

VirtualMachine::VirtualMachine() : jump(0) {
}

void VirtualMachine::execute(VirtualMachine::OpCodes opCode, VirtualMachine::MemType operand) {
    if (jump) {
        jump--;
        return;
    }

    states.emplace_back(std::make_pair(opCode, operand));

    switch (opCode) {
        case OpCodes::PUSH: {
            stack.push_back(operand);
            break;
        }
        case OpCodes::POP: {
            if (stack.empty())
                throw std::logic_error("Stack Underflow Error");
            stack.pop_back();
            break;
        }
        case OpCodes::ADD: {
            MemType add{ stack.back() };
            execute(OpCodes::POP);
            add += stack.back();
            execute(OpCodes::POP);
            execute(OpCodes::PUSH, add);
            break;
        }
        case OpCodes::SUB: {
            MemType sub{ stack.back() };
            execute(OpCodes::POP);
            sub -= stack.back();
            execute(OpCodes::POP);
            execute(OpCodes::PUSH, sub);
            break;
        }
        case OpCodes::MUL: {
            MemType mul{ stack.back() };
            execute(OpCodes::POP);
            mul *= stack.back();
            execute(OpCodes::POP);
            execute(OpCodes::PUSH, mul);
            break;
        }
        case OpCodes::DIV: {
            MemType div{ stack.back() };
            execute(OpCodes::POP);
            if (stack.back() == 0)
                throw std::logic_error("Math Error: Division by zero");
            div /= stack.back();
            execute(OpCodes::POP);
            execute(OpCodes::PUSH, div);
            break;
        }
        case OpCodes::PRINT: {
            std::cout << stack.back() << std::endl;
            break;
        }
        case OpCodes::INPUT: {
            MemType input;
            std::cin >> input;
            execute(OpCodes::PUSH, input);
            break;
        }
        case OpCodes::JUMP: {
            if (operand > 0) {
                jump = operand;
                break;
            }
            if (std::abs(operand) >= states.size())
                throw std::logic_error("Stack Overflow Error");
            auto previous{ states.size() - 1 + operand };
            for (auto i{ previous }; i < states.size(); i++) {
                execute(states[i].first, states[i].second);
            }
            break;
        }
    }
}