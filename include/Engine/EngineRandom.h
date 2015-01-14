#ifndef ENGINERANDOM_H
#define ENGINERANDOM_H

#include <random>
#include "EngineExport.h"

namespace se
{

class SEVENGINEDLL_API Random
{
public:
	static Random& get();

	int Int(int min, int max);
	double Double(double min, double max);

private:
	Random();
	Random(Random const&) {}
	void operator=(Random const&) {}
};
}

#endif // ENGINERANDOM_H