#include <iostream>

#include "GeneticTrainer.h"

int main()
{
	TrainerPolicy policy
	{
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