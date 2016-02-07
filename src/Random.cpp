#include"Random.hpp"
int Random::Rand()
{
	if (distribution==0)
		{return (*linearDistribution)(*prandom);}
	if (distribution==1)
	{
		int temp= (*linearDistribution)(*prandom);
		if (temp)
			{
			temp = 0;
			while (temp == 0)
				{temp=(*normal1)(*prandom);}
			return temp;
			}
		else
			{
			temp = 0;
			while (temp == 0)
				{temp=(*normal2)(*prandom);}
			return temp;
			}
	}
	
}
Random::~Random()
{
	//printf("Random::~Randmo\n");
}

Random::Random()// :rd(new std::random_device)
{

	std::shared_ptr<std::random_device> rd;
	bool error = false;
	try
	{
	std::shared_ptr<std::random_device> temp2( new std::random_device());
	rd = temp2;
	}
	catch (std::exception e)
	{
	error = true;
	}
	//printf("Random::Randmo\n");
	if (error)
	{
	std::srand(std::time(nullptr));
	std::shared_ptr<std::mt19937> temp( new std::mt19937(std::rand()));
	prandom=temp;
	}
	else
	{
	std::shared_ptr<std::mt19937> temp( new std::mt19937((*rd)()));
	prandom=temp;
	}
	linearDistribution=nullptr;
}
Random::Random(int lower, int upper, int distribution) : Random() // :rd(new std::random_device)
{
	this->distribution = distribution;
	//std::shared_ptr<std::mt19937> temp( new std::mt19937((*rd)()));
//	prandom=temp;
	if (distribution==0)
	{
		std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(lower,upper));
		linearDistribution=temp2;
	}
	if (distribution==1)
	{
		std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(0,1));
		linearDistribution=temp2;
		std::shared_ptr<std::binomial_distribution<int>> tnormal(new std::binomial_distribution<int>(lower*2,0.5));
		normal1=tnormal;
		std::shared_ptr<std::binomial_distribution<int>> tnormal2(new std::binomial_distribution<int>(upper*2,0.5));
		normal2=tnormal2;
	}
}
void Random::Change(int lower, int upper, int distribution)
{
	this->distribution = distribution;
	if (distribution==0)
	{
		std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(lower,upper));
		linearDistribution=temp2;
	}
	if (distribution==1)
	{
		std::shared_ptr<std::uniform_int_distribution<int>> temp2(new std::uniform_int_distribution<int>(0,1));
		linearDistribution=temp2;
		std::shared_ptr<std::binomial_distribution<int>> tnormal(new std::binomial_distribution<int>(lower*2,0.5));
		normal1=tnormal;
		std::shared_ptr<std::binomial_distribution<int>> tnormal2(new std::binomial_distribution<int>(upper*2,0.5));
		normal2=tnormal2;
		
	}

}
