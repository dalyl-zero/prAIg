#include <iostream>
#include <algorithm>

#include "Mutator.h"

int main()
{
//	std::vector<Code> minmax{
//            {OpCode::JMP, 32},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'h'},
//            {OpCode::PUSH, 'g'},
//            {OpCode::PUSH, 'i'},
//            {OpCode::PUSH, 'H'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::JMP, 15},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'w'},
//            {OpCode::PUSH, 'o'},
//            {OpCode::PUSH, 'L'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::PUSH, ':'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'b'},
//            {OpCode::PUSH, 'm'},
//            {OpCode::PUSH, 'u'},
//            {OpCode::PUSH, 'n'},
//            {OpCode::PUSH, ' '},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'h'},
//            {OpCode::PUSH, 't'},
//            {OpCode::PUSH, ' '},
//            {OpCode::PUSH, 's'},
//            {OpCode::PUSH, 's'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'u'},
//            {OpCode::PUSH, 'G'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//
//            {OpCode::PUSH, 29}, // The random number ! Please make it random :(
//            {OpCode::INPUT},
//            {OpCode::SUB},
//            {OpCode::DUP},
//
//            {OpCode::JIP, -54},
//            {OpCode::JIN, -72},
//
//            {OpCode::PUSH, '!'},
//            {OpCode::PUSH, 't'},
//            {OpCode::PUSH, 'c'},
//            {OpCode::PUSH, 'e'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'r'},
//            {OpCode::PUSH, 'o'},
//            {OpCode::PUSH, 'C'},
//            {OpCode::PUSH, '\n'},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//            {OpCode::PRINT_CHAR},
//	};
//
//	vm.executeProgram(minmax);

	std::vector<Code> fibonacci
	{
		{OpCode::PUSH, 0},
		{OpCode::PUSH, 1},

		{OpCode::PUSH, 45},
		{OpCode::POP, 0, 2},

		{OpCode::POP, 0, 0},
		{OpCode::POP, 0, 1},

		{OpCode::PUSH, 0},

		{OpCode::ADD, 0, 0},
		{OpCode::ADD, 0, 1},

		{OpCode::DUP, 0},
		{OpCode::PRINT, 0},

		{OpCode::SWAP, 0, 0},
		{OpCode::POP, 0, 1},

		{OpCode::PUSH, 0, 1},
		{OpCode::PUSH, 0, 0},

		{OpCode::PUSH, 0, 2},
		{OpCode::SUB, 1},

		{OpCode::JIP, -14}
	};

	VirtualMachine vm;
	vm.executeProgram(fibonacci);
	std::cout << vm.getOutput() << std::endl;

	std::vector<std::pair<Program, int>> bestPrograms;

	auto getScore = [](const std::string& output)
	{
		//const std::string target = "Hello World!";
		const std::string target = "Hell";

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