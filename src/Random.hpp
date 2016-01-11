#pragma once
#include <random>
/*
losuje liczby z zadanego przedziału z rozkładem liniowym
*/
class Random
{
	public:
	int Rand();
	~Random();
	Random(int lower, int upper);
	Random();
	void Change(int lower, int upper);
	private:
	std::random_device rd;
	std::default_random_engine *prandom=nullptr;
	std::uniform_int_distribution<int> *distribution=nullptr;
};
