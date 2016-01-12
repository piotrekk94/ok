#include"Random.hpp"
int Random::Rand()
{
	return (*distribution)(*prandom);
}
Random::~Random()
{
	printf("Random::~Randmo\n");
}

Random::Random() :rd(new std::random_device)
{
	printf("Random::Randmo\n");
	std::shared_ptr<std::default_random_engine> temp( new std::default_random_engine((*rd)()));
	prandom=temp;
	distribution=nullptr;
}
Random::Random(int lower, int upper)  :rd(new std::random_device)
{
	std::shared_ptr<std::default_random_engine> temp( new std::default_random_engine((*rd)()));
	prandom=temp;
	std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(lower,upper));
	distribution=temp2;
}
void Random::Change(int lower, int upper)
{
	std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(lower,upper));
	distribution=temp2;

}
