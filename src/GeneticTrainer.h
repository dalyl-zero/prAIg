//
// Created by Dalyl on 17/09/2018.
//

#pragma once

#include "VirtualMachine.h"
#include "Mutator.h"

class GeneticTrainer
{
public:
    void train();

private:
    int score(const std::string& output);
    VirtualMachine vm;
    Mutator mutator;
};
