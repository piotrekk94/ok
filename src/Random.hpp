#pragma once
#include <random>
#include <memory>
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
	std::shared_ptr<std::random_device> rd;
	std::shared_ptr<std::default_random_engine> prandom;
	std::shared_ptr<std::uniform_int_distribution<int>> distribution;
};
