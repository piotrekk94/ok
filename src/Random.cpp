#include"Random.hpp"
int Random::Rand()
{
	return (*distribution)(*prandom);
}
Random::~Random()
{
	delete prandom;
	delete distribution;
}
Random::Random()
{
	prandom = new std::default_random_engine(rd());
	distribution=nullptr;
}
Random::Random(int lower, int upper)
{
	prandom = new std::default_random_engine(rd());
	distribution = new std::uniform_int_distribution<int>(lower,upper);
}
void Random::Change(int lower, int upper)
{
	delete distribution;
	distribution = new std::uniform_int_distribution<int>(lower,upper);

}
