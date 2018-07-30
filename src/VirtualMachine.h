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
    void setCode(OpCodes opCode, MemType operand = 0);
    void execute();

private:
    std::vector<MemType> stack;
    MemType executionAddress;
    std::vector<std::pair<OpCodes, MemType> > code;
};


#endif //PRAIG_VIRTUALMACHINE_H
