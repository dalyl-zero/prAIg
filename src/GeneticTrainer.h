//
// Created by Dalyl on 17/09/2018.
//

#pragma once

#include <functional>

#include "VirtualMachine.h"
#include "Mutator.h"

struct TrainerPolicy
{
	std::function<int(const std::string& output)> getScore;
};

class GeneticTrainer
{
public:
    GeneticTrainer(const TrainerPolicy& policy, int programs, int best, int iterations);
    void train();

private:
	TrainerPolicy policy;

    int numPrograms;
    int bestCnt;
    int iterationCnt;

    VirtualMachine vm;
    Mutator mutator;
};
