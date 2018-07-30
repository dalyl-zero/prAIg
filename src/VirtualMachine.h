//
// Created by Dalyl on 30/07/2018.
//

#ifndef PRAIG_VIRTUALMACHINE_H
#define PRAIG_VIRTUALMACHINE_H

#include <vector>

class VirtualMachine {
public:
    using MemType = int;
    enum class OpCodes {
        PUSH,
        POP,
        ADD,
        SUB,
        MUL,
        DIV,
        PRINT,
        INPUT,
        JUMP
    };

    VirtualMachine();
    void execute(OpCodes opCode, MemType operand = 0);
private:
    std::vector<MemType> stack;
    MemType jump;
    std::vector<std::pair<OpCodes, MemType> > states;
};


#endif //PRAIG_VIRTUALMACHINE_H
