//
// Created by Dalyl on 07/08/2018.
//

#include "GeneticTrainer.h"

#include <algorithm>
GeneticTrainer::GeneticTrainer(const TrainerPolicy& policy, int programs, int best, int iterations) : policy{policy}, numPrograms{programs}, bestCnt{best}, iterationCnt{iterations}
{}

void GeneticTrainer::train()
{
    std::vector<std::pair<Program, int>> bestPrograms;

    for(int x = 0; x < numPrograms; x++)
    {
        Program randomProgram = mutator.generateProgram(800);
        vm.executeProgramSafe(randomProgram); // Lord, have mercy.

        bestPrograms.emplace_back(std::make_pair(randomProgram, policy.getScore(vm.getOutput())));
    }

    for(int x = 0; x < iterationCnt; x++)
    {
        std::sort(bestPrograms.begin(), bestPrograms.end(), [](const auto& p1, const auto& p2)
        {
            return p1.second > p2.second;
        });

        if(x % bestCnt == 0)
        {
            vm.executeProgramSafe(bestPrograms[0].first);
            std::cout << "Best Output: " << bestPrograms[0].second << " | " << vm.getOutput() << std::endl;

            if(bestPrograms[0].second == 0)
            {
                break;
            }
        }

        bestPrograms.resize(std::min(bestPrograms.size(), (size_t)10));

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