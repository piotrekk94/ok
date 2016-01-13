#include <vector>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int starting_population=100;
	int survival_amount=20;
	int mutation_percent=30;
	int mutation_amount=5;
	int crossover_percent=70;
	int tournament_groupsize=4;
	int MaxLength=300;
	int MaintanceBreaks=10;
	int MaintanceBreaksAvgLength=10;
	int Tasks=50;
	int TasksAvgLength=15;
	int Duration=2;
	for(int i=0;i<10;i++)
	{
		Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize);
		job.Start(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,Duration);
	}
	return 0;
}
