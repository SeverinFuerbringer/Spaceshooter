#include "EngineRandom.h"

std::random_device rd;

namespace se
{

Random::Random()
{
}


Random& Random::get()
{
	static Random instance;
	return instance;
}


int Random::Int(int min, int max)
{
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}


double Random::Double(double min, double max)
{
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min, max);

	return dist(mt);
}
}