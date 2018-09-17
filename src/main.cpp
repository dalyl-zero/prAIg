#include <iostream>

#include "GeneticTrainer.h"

int main()
{
    GeneticTrainer geneticTrainer(1000, 100, 10000);
    geneticTrainer.train();

	return 0;
}