#include <vector>
#include <string>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int j=0,k=0;
	FILE* plik;
	plik=fopen("test.csv","w");
	int MaxLength=25000;
	int MaintanceBreaks=250;
	int MaintanceBreaksAvgLength=5;
	int Tasks=500;
	int TasksAvgLength=50;
	int Duration=30000;
	int starting_population=100;
	int survival_amount=100;
	int change_check_distance=100;
	Instance inst;
	int temp;
	scanf("%d",&temp );
	bool load=temp;
	scanf("%d",&temp );
	//bool save=!load;
	bool save=false;
	bool randanswer=temp;
	if (randanswer)starting_population*=1000;
	int instancenumber=0;

	int mutation_percent;
	int crossover_percent;


	if (load)
	{
		Solution temp;
		std::stringstream si;
		si<<"./input/i"<<instancenumber<<".txt";
		inst=temp.Load_Instance((si.str()).c_str());
		Tasks=inst.task.size();
		MaintanceBreaks=inst.maintance.size();
	}

	Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
	std::vector<Solution> solutions=gen.GenerateSolution();
	if (load)
	{
		gen.ReplaceBreaks(inst);
		gen.ReplaceTasks(inst);
	}
	if (save)
	{
		std::stringstream so;
		so<<"./input/i"<<instancenumber<<".txt";
		solutions[0].Save_Instance((so.str()).c_str(),instancenumber);
	}

	while (j<2)
	{
		printf("%d %d\n",j,k );

		int mutation_amount=1;
		int tournament_groupsize=3;
		if (!randanswer)
			{
				switch (j) {
					case 0:
						mutation_percent=k*5;
						crossover_percent=100-mutation_percent;
						k++;
						fprintf(plik, "mutation/crossover,%d,%d,",mutation_percent,crossover_percent );
						if (k==21)
						{
							j++;
							k=1;
						}
						break;
					case 1:
						mutation_amount=k;
						mutation_percent=30;
						crossover_percent=70;
						k++;
						fprintf(plik, "mutation_amount,%d,",mutation_amount );
						if (k==5)
						{
							j++;
							k=1;
						}
						break;
				}
			}
		int sum=0;
		int sum2=0;
		int powt=1;
		int length=0;
		std::clock_t c_end,c_start;
		int t=0;
		for(int i=0;i<powt;i++)
		{
			int prev_mp,prev_cp;
			Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,change_check_distance,randanswer);
			c_start=std::clock();
			job.Start(solutions,Duration);
			c_end=std::clock();
			sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
			sum2+=job.minhistory[0];
			length+=job.minhistory.size();
			t+=1000*(c_end-c_start)/CLOCKS_PER_SEC;
		}
		fprintf(plik,"%d,%d,%d\n",100*sum/sum2,length/powt,t/powt);
	}
	fclose(plik);
		return 0;
}
