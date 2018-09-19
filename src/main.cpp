#include <iostream>

#include "GeneticTrainer.h"

int main()
{
	TrainerPolicy policy
	{
		[](Mutator& mutator)
		{
			mutator.randomMutate = std::uniform_int_distribution<int>{0, 700};
		    mutator.randomOperand = std::uniform_int_distribution<int>{10, 122};
		    mutator.randomRegister = std::uniform_int_distribution<int>{-1, -1};

		    mutator.setOpCodeWeights(
		    {
		        {OpCode::PUSH, 100},
		        {OpCode::PRINT_CHAR, 100},
		    });

		    mutator.setCodeMutationWeights(
		    {
		        {Mutator::INCREMENT_OPERAND, 30},
		        {Mutator::DECREMENT_OPERAND, 30},
		        {Mutator::INCREMENT_REGISTER, 0},
		        {Mutator::DECREMENT_REGISTER, 0},
		        {Mutator::NEW_OPCODE, 2},
		        {Mutator::NEW_OPERAND, 2},
		        {Mutator::NEW_REGISTER, 0}
		    });
		},

		[](const std::string& output)
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
	};

    GeneticTrainer geneticTrainer(policy, 1000, 100, 10000);
    geneticTrainer.train();

	return 0;
}