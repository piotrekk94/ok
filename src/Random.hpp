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
	// 0 - uniform_int_distribution
	// 1 - 2 punktowy rozklad
	~Random();
	Random(int lower, int upper, int distribution = 0);
	Random();
	void Change(int lower, int upper, int distribution = 0);
	private:
	int distribution;
	std::shared_ptr<std::random_device> rd;
	std::shared_ptr<std::mt19937> prandom;
	std::shared_ptr<std::uniform_int_distribution<int>> linearDistribution;
	std::shared_ptr<std::binomial_distribution<int>> normal1,normal2;
};
