#include "Randomizer.h"

int Randomizer::GetRandomNumber(int Min, int Max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(Min, Max);

	return dist6(rng);
}