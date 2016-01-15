#include <vector>
#include <string>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int j=0,k=1;
	FILE* plik;
	plik=fopen("test.csv","w");
	int MaxLength=10000;
	int MaintanceBreaks=20;
	int MaintanceBreaksAvgLength=100;
	int Tasks=200;
	int TasksAvgLength=50;
	int Duration=5000;
	int starting_population=100;
	int survival_amount=50;
	Instance inst;
	int temp;
	scanf("%d",&temp );
	bool load=temp;
	bool save=!load;
	int instancenumber=0;

	if (load)
	{
		Solution temp;
		std::stringstream si;
		si<<"./input/i"<<instancenumber<<".txt";
		Instance inst=temp.Load_Instance((si.str()).c_str());
		//Tasks=inst.task.size();
		//MaintanceBreaks=inst.maintance.size();
	}

	Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
	std::vector<Solution> solutions=gen.GenerateSolution();
	if (load)
	{
		//gen.ReplaceBreaks(inst);
		//gen.ReplaceTasks(inst);
	}
	if (save)
	{
		std::stringstream so;
		so<<"./input/i"<<instancenumber<<".txt";
		solutions[0].Save_Instance((so.str()).c_str(),instancenumber);
	}

	while (j<3)
	{
		printf("%d %d\n",j,k );

		int mutation_percent=30;
		int crossover_percent=70;
		int mutation_amount=1;
		int tournament_groupsize=3;
		switch (j) {
			case 0:
				mutation_percent=k*5;
				k++;
				fprintf(plik, "mutation_percent,%d,",mutation_percent );
				if (k==21)
				{
					j++;
					k=1;
				}
				break;
			case 1:
				crossover_percent=k*5;
				k++;
				fprintf(plik, "crossover_percent,%d,",crossover_percent );
				if (k==21)
				{
					j++;
					k=1;
				}
				break;
			case 2:
				mutation_amount=k;
				k++;
				fprintf(plik, "mutation_amount,%d,",mutation_amount );
				if (k==5)
				{
					j++;
					k=1;
				}
				break;
		}
		int sum=0;
		int sum2=0;
		int powt=3;
		for(int i=0;i<powt;i++)
		{
			//std::vector<Solution> solutions=gen.GenerateSolution();
			Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,20);
			job.Start(solutions,Duration);
			sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
			sum2+=job.minhistory[0];
		}
		fprintf(plik,"%d\n",100*sum/sum2);
	}
	fclose(plik);
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
