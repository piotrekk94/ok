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
	int Duration=5000;
	int starting_population=100;
	int survival_amount=100;
	int change_check_distance=100;
	int mutation_percent=30;
	int crossover_percent=70;
	int mutation_amount=1;
	int tournament_groupsize=3;
	Instance inst;
	int temp;
	int instancenumber;
	int sum=0;
	int sum2=0;
	int powt=1;
	int length=0;
	std::clock_t c_end,c_start;
	int t=0;
	bool roulette=false,load=false,save=false,randanswer=false,params=false;

	printf("Zaladowac instancje ? 1 - tak 0 - nie\n");
	scanf("%d",&temp );
	load=temp;
	if (!load){
		printf("Parametry instancji ? 1 - recznie 0 - domyslne\n");
		scanf("%d",&temp );
		params=temp;
	}
	if (params){
		printf("MaxLength:%d\n",MaxLength);
		scanf("%d",&MaxLength );
		printf("MaintanceBreaks:%d\n",MaintanceBreaks);
		scanf("%d",&MaintanceBreaks );
		printf("MaintanceBreaksAvgLength:%d\n",MaintanceBreaksAvgLength);
		scanf("%d",&MaintanceBreaksAvgLength );
		printf("Tasks:%d\n",Tasks);
		scanf("%d",&Tasks );
		printf("TasksAvgLength:%d\n",TasksAvgLength);
		scanf("%d",&TasksAvgLength );
		printf("Duration:%d\n",Duration);
		scanf("%d",&Duration );
		printf("starting_population:%d\n",starting_population);
		scanf("%d",&starting_population );
		printf("survival_amount:%d\n",survival_amount);
		scanf("%d",&survival_amount );
		printf("change_check_distance:%d\n",change_check_distance);
		scanf("%d",&change_check_distance );
		printf("mutation_percent:%d\n",mutation_percent);
		scanf("%d",&mutation_percent );
		printf("crossover_percent:%d\n",crossover_percent);
		scanf("%d",&crossover_percent );
		printf("mutation_amount:%d\n",mutation_amount);
		scanf("%d",&mutation_amount );
		printf("tournament_groupsize:%d\n",tournament_groupsize);
		scanf("%d",&tournament_groupsize );
	}
	printf("Wygenerowac rozwiazanie losowo? 1 - tak 0 - nie\n");
	scanf("%d",&temp );
	randanswer=temp;
	if (!load){
		printf("Zapisac instancje ? 1 - tak 0 - nie\n");
		save=temp;
	}
	if (load||save){
		printf("Podaj numer instancji\n");
		scanf("%d",&temp );
		instancenumber=temp;
	}
	if (randanswer)starting_population=1;

	printf("Sposob selekcji 1 - ruletka 0 - turniej \n");
	scanf("%d",&temp );
	roulette=temp;

	printf("Ilosc powtorzen:%d\n",powt);
	scanf("%d",&powt );

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


	for(int i=0;i<powt;i++)
	{
		Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,change_check_distance,randanswer,roulette);
		c_start=std::clock();
		job.Start(solutions,Duration);
		c_end=std::clock();
		sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
		sum2+=job.minhistory[0];
		length+=job.minhistory.size();
		t+=1000*(c_end-c_start)/CLOCKS_PER_SEC;
	}
	fprintf(plik,"%d,%d,%d\n",100*sum/sum2,length/powt,t/powt);
	fclose(plik);
	return 0;
}
