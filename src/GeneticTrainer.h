//
// Created by Dalyl on 17/09/2018.
//

#pragma once

#include <functional>

#include "VirtualMachine.h"
#include "Mutator.h"

struct TrainerPolicy
{
	std::function<void(Mutator& mutator)> initMutator;
	std::function<int(const std::string& output)> getScore;
};

class GeneticTrainer
{
public:
    void train();

	TrainerPolicy policy;

    int initialProgramCount;
    int populationCount;
    int maxIterationCount;

private:
    VirtualMachine vm;
    Mutator mutator;
};
