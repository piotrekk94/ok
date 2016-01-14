#include <vector>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int j=0,k=1;
	FILE* plik;
	plik=fopen("test.csv","w");
	int MaxLength=500;
	int MaintanceBreaks=50;
	int MaintanceBreaksAvgLength=5;
	int Tasks=100;
	int TasksAvgLength=5;
	int Duration=1;

	int survival_amount=20;
	int starting_population=100;
	Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
	std::vector<Solution> solutions=gen.GenerateSolution();
	for (int i=0;i<1;i++)
		solutions[i].Save_Instance("plik.txt",i);
	while (j<5)
	{
		printf("%d %d\n",j,k );
		solutions.clear();
		/*for (int i=0;i<starting_population;i++)
		{
			Solution solution;
			std::vector<Answer> answer;
			Instance instance = solution.Load_Instance((std::to_string(i).c_str()));
			answer=GenerateAnswers(instance.task);
			Solution solution2(&(instance.task.front()),&answer,&(instance.maintance.front()),&(instance.maintance.front()),instance.task.size(),instance.maintance.size(),instance.maintance.size());
			solutions.push_back(solution2);
		}*/
		int mutation_percent=30;
		int crossover_percent=70;
		int mutation_amount=5;
		int tournament_groupsize=4;
		switch (j) {
			case 0:
				mutation_percent=k*10;
				k++;
				fprintf(plik, "mutation_percent %d,",mutation_percent );
				if (k==10)
				{
					j++;
					k=1;
				}
				break;
			case 1:
				crossover_percent=k*10;
				k++;
				fprintf(plik, "crossover_percent %d,",crossover_percent );
				if (k==10)
				{
					j++;
					k=1;
				}
				break;
			case 2:
				mutation_amount=k;
				k++;
				fprintf(plik, "mutation_amount %d,",mutation_amount );
				if (k==10)
				{
					j++;
					k=1;
				}
				break;
			case 3:
				tournament_groupsize=k;
				k++;
				fprintf(plik, "tournament_groupsize %d,",tournament_groupsize );
				if (k==10)
				{
					j++;
					k=1;
				}
				break;
		}
		int sum=0;
		int powt=20;
		for(int i=0;i<powt;i++)
		{
			Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize);
			job.Start(solutions,Duration);
			sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
		}
		fprintf(plik,"%d\n",sum/powt);
	}
	/*
		Solution solution;
		std::vector<Answer> answer;
		Instance instance = solution.Load_Instance("12.txt");
		answer=GenerateAnswers(instance.task);
		Solution solution2(&(instance.task.front()),&answer,&(instance.maintance.front()),&(instance.maintance.front()),instance.task.size(),instance.maintance.size(),instance.maintance.size());
		solution2.Save_Instance("13.txt",13);
	 */
	return 0;
}
