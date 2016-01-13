#include <vector>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int starting_population=50;
	int survival_amount=20;
	int mutation_percent=30;
	int mutation_amount=4;
	int crossover_percent=70;
	int tournament_groupsize=4;
	int MaxLength=300;
	int MaintanceBreaks=10;
	int MaintanceBreaksAvgLength=10;
	int Tasks=50;
	int TasksAvgLength=15;
	int Duration=1;
	FILE* plik;
	plik=fopen("test.csv","w");
	for(int i=1;i<10;i++)
	{
		Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize);
		job.Start(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,Duration);
	}
	/*	
		Solution solution;
		std::vector<Answer> answer;
		Instance instance = solution.Load_Instance("12.txt");
		Solution solution2(&(instance.task.front()),&answer,&(instance.maintance.front()),&(instance.maintance.front()),instance.task.size(),instance.maintance.size(),instance.maintance.size());
		solution2.Save_Instance("13.txt",13);
	 */
	return 0;
}
