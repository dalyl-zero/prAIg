//
// Created by Dalyl on 07/08/2018.
//

#include "GeneticTrainer.h"

#include <algorithm>

int GeneticTrainer::score(const std::string &output)
{
    const std::string target = "LlzGRnCDajkw6oNjgL7hsS3ncuFjeZ121lvHvI9DJDZlUBQ3hxF47MHER0vjgHUJrSpePzr6bNkOSjZZ4KmgUrpLFcKxInKBDFaUacKA14c6AZOfHf9UcK6UKr6uexMq";

    int score {0};

    for(size_t x {0}; x < target.size() && x < output.size(); x++)
    {
        score -= std::abs(target[x] - output[x]);
    }

    score -= std::abs((int)(target.size()) - (int)(output.size())) * 255;

    return score;
}

void GeneticTrainer::train()
{
    std::vector<std::pair<Program, int>> bestPrograms;

    for(int x = 0; x < 10000; x++)
    {
        Program randomProgram = mutator.generateProgram(800);
        vm.executeProgramSafe(randomProgram); // Lord, have mercy.

        bestPrograms.emplace_back({randomProgram, score(vm.getOutput())});
    }

    for(int x = 0; x < 100000; x++)
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

        bestPrograms.resize(std::min(bestPrograms.size(), (size_t)10));

        std::vector<std::pair<Program, int>> newPrograms = bestPrograms;
        for(auto& pair : newPrograms)
        {
            mutator.mutate(pair.first);
            vm.executeProgramSafe(pair.first);
            pair.second = score(vm.getOutput());
        }

        bestPrograms.insert(bestPrograms.end(), newPrograms.begin(), newPrograms.end());
    }
}