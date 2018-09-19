//
// Created by Dalyl on 07/08/2018.
//

#include "GeneticTrainer.h"

#include <algorithm>

void GeneticTrainer::train()
{
    policy.initMutator(mutator);

    std::vector<std::pair<Program, int>> bestPrograms;

    for(int x = 0; x < initialProgramCount; x++)
    {
        Program randomProgram = mutator.generateProgram(800);
        vm.executeProgramSafe(randomProgram); // Lord, have mercy.

        bestPrograms.emplace_back(std::make_pair(randomProgram, policy.getScore(vm.getOutput())));
    }

    for(int x = 0; x < maxIterationCount; x++)
    {
        std::sort(bestPrograms.begin(), bestPrograms.end(), [](const auto& p1, const auto& p2)
        {
            return p1.second > p2.second;
        });

        if(x % 100 == 0)
        {
            vm.executeProgramSafe(bestPrograms[0].first);
            std::cout << "Best Output: " << bestPrograms[0].second << " | " << vm.getOutput() << std::endl;

            if(bestPrograms[0].second == 0)
            {
                break;
            }
        }

        bestPrograms.resize(std::min(bestPrograms.size(), static_cast<size_t>(populationCount)));

        std::vector<std::pair<Program, int>> newPrograms = bestPrograms;
        for(auto& pair : newPrograms)
        {
            mutator.mutate(pair.first);
            vm.executeProgramSafe(pair.first);
            pair.second = policy.getScore(vm.getOutput());
        }

        bestPrograms.insert(bestPrograms.end(), newPrograms.begin(), newPrograms.end());
    }
}