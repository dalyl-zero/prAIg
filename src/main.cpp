#include <iostream>
#include <algorithm>

#include "Mutator.h"

int main()
{
	VirtualMachine vm;

	std::vector<std::pair<Program, int>> bestPrograms;

	auto getScore = [](const std::string& output)
	{
		//const std::string target = "Hello World!";
		const std::string target = "dumb";

		int score = 0;

		for(int x = 0; x < target.size() && x < output.size(); x++)
		{
			score -= std::abs(target[x] - output[x]);
		}

		score -= std::abs((int)(target.size() - output.size())) * 255;

		return score;
	};

	for(int x = 0; x < 1000; x++)
	{
		Program randomProgram = Mutator::generateCode();
		try
		{
			vm.executeProgram(randomProgram); // Lord, have mercy.
		}
		catch(std::logic_error exception)
		{
			//std::cout << exception.what() << std::endl;
		}

		if(vm.getOutput().size())
		{
			//std::cout << "Output: " << vm.getOutput() << std::endl;
		}

		bestPrograms.push_back({randomProgram, getScore(vm.getOutput())});

		//std::cout << "Next program" << std::endl << std::endl;
	}

	for(int x = 0; x< 10000; x++)
	{
		std::sort(bestPrograms.begin(), bestPrograms.end(), [](auto& p1, auto& p2)
		{
			return p1.second > p2.second;
		});

		bestPrograms.resize(std::min(bestPrograms.size(), (size_t)500));

		std::vector<std::pair<Program, int>> newPrograms = bestPrograms;
		for(auto& pair : newPrograms)
		{
			Mutator::mutate(pair.first);
		}

		bestPrograms.insert(bestPrograms.end(), newPrograms.begin(), newPrograms.end());

		for(auto& pair : bestPrograms)
		{
			try
			{
				vm.executeProgram(pair.first);
			}
			catch(std::logic_error exception)
			{
				//std::cout << exception.what() << std::endl;
			}

			if(vm.getOutput().size())
			{
				//std::cout << "Output: " << vm.getOutput() << std::endl;
			}

			pair.second = getScore(vm.getOutput());
		}

		try
		{
			vm.executeProgram(bestPrograms[0].first);
		}
		catch(std::logic_error exception)
		{
		}
		std::cout << "Best Output: " << vm.getOutput() << std::endl;
	}

	return 0;
}