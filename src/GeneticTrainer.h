//
// Created by Dalyl on 17/09/2018.
//

#pragma once

#include "VirtualMachine.h"
#include "Mutator.h"

class GeneticTrainer
{
public:
    GeneticTrainer(int programs, int best, int iterations);
    void train();

private:
    int score(const std::string& output);
    int num_programs;
    int best_cnt;
    int iteration_cnt;
    VirtualMachine vm;
    Mutator mutator;
};
