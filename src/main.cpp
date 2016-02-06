#include <vector>
#include <string>
#include "Work.hpp"
using namespace std;

int main(int argc,char** argv)
{
	int j=0,k=1,l=0;
	FILE* plik;
	plik=fopen("test.csv","w");
	int temp,instancenumber,sum=0,sum2=0,powt=10,length=0,t=0;
	std::clock_t c_end,c_start;

	//////////////////////////////
	int MaxLength=3500;
	int MaintanceBreaks=100;
	int MaintanceBreaksAvgLength=10;
	int Tasks=50;
	int TasksAvgLength=50;
	int starting_population=100;
	int Duration=50000;
	//////////////////////////////
	int survival_amount=100;
	int change_check_distance=20;
	int mutation_percent=30;
	int crossover_percent=70;
	int mutation_amount=1;
	int tournament_groupsize=3;
	//////////////////////////////

	std::vector<std::vector<Solution>> vsolutions;

	bool roulette=false,load=false,save=false,randanswer=false,params=false,savebest=false,autotest=false;

	printf("Przeprowadzic wszystkie testy automatycznie ? 1 - tak 0 - nie\n");
	scanf("%d",&temp );
	autotest=temp;
	if (!autotest){
		printf("Zaladowac instancje ? 1 - tak 0 - nie\n");
		scanf("%d",&temp );
		load=temp;
		printf("Wygenerowac rozwiazanie losowo? 1 - tak 0 - nie\n");
		scanf("%d",&temp );
		randanswer=temp;
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
			/*printf("starting_population:%d\n",starting_population);
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
			scanf("%d",&tournament_groupsize );*/
		}
		if (!load){
			printf("Zapisac instancje ? 1 - tak 0 - nie\n");
			scanf("%d",&temp );
			save=temp;
		}
		printf("Zapisac najlepsze rozwiazanie ? 1 - tak 0 - nie\n");
		scanf("%d",&temp );
		savebest=temp;
		if (load||save||savebest){
			printf("Podaj numer instancji\n");
			scanf("%d",&temp );
			instancenumber=temp;
		}
	}
	else {
		save=true;
		savebest=true;
		load=false;
	}
	if (randanswer){
		starting_population=1;
		Duration/=10;
	}
	printf("Sposob selekcji 1 - ruletka 0 - turniej \n");
	scanf("%d",&temp );
	roulette=temp;
	if (!autotest)powt=1;
	for (int i=0;i<6;i++){
		if (!autotest) i=6;
		else {
			switch (i) {
				case 0:
					MaintanceBreaks=50;
					MaintanceBreaksAvgLength=100;
					Tasks=200;
					TasksAvgLength=50;
					break;
				case 1:
					MaintanceBreaks=50;
					MaintanceBreaksAvgLength=100;
					Tasks=25;
					TasksAvgLength=400;
					break;
				case 2:
					MaintanceBreaks=1000;
					MaintanceBreaksAvgLength=10;
					Tasks=200;
					TasksAvgLength=50;
					break;
				case 3:
					MaintanceBreaks=100;
					MaintanceBreaksAvgLength=100;
					Tasks=200;
					TasksAvgLength=50;
					break;
				case 4:
					MaintanceBreaks=100;
					MaintanceBreaksAvgLength=100;
					Tasks=200;
					TasksAvgLength=50;
					break;
				case 5:
					MaintanceBreaks=100;
					MaintanceBreaksAvgLength=100;
					Tasks=200;
					TasksAvgLength=50;
					break;
			}
		}
		if (load)
		{
			Solution temp;
			Instance inst;
			std::stringstream si;
			si<<"i"<<instancenumber<<".txt";
			inst=temp.Load_Instance((si.str()).c_str());
			Tasks=inst.task.size();
			MaintanceBreaks=inst.maintance.size();
			Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
			gen.ReplaceBreaks(inst);
			gen.ReplaceTasks(inst);
			std::vector<Solution> solutions=gen.GenerateSolution();
			vsolutions.push_back(solutions);
		}
		else
			for (int j=0;j<10;j++){
				Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
				std::vector<Solution> solutions=gen.GenerateSolution();
				vsolutions.push_back(solutions);
				if (!autotest)break;
			}
		if (save)
		{
			if (autotest)
				for (int j=0;j<vsolutions.size();j++){
					std::stringstream so;
					so<<"i"<<i<<j<<".txt";
					vsolutions[j][0].Save_Instance((so.str()).c_str(),i*10+j);
				}
			else {
				std::stringstream so;
				so<<"i"<<instancenumber<<".txt";
				vsolutions[0][0].Save_Instance((so.str()).c_str(),instancenumber);
			}
		}
		j=sum=sum2=0;
		for(int j=0;j<powt;j++)
		{
			if (autotest)printf("%d %d\n",i,j);
			Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,change_check_distance,randanswer,roulette);
			c_start=std::clock();
			job.Start(vsolutions[j],Duration);
			c_end=std::clock();
			sum+=job.minhistory[0]-job.minhistory.back();
			sum2+=job.minhistory[0];
			length+=job.minhistory.size();
			t+=1000*(c_end-c_start)/CLOCKS_PER_SEC;
			if (savebest){
				int max=0;
				for (int h=0;h<vsolutions[j].size();h++)
					max = vsolutions[j][h].getRate() < vsolutions[j][max].getRate() ? h : max;
				std::stringstream so;
				if (autotest){
					so<<"o"<<i<<j<<".txt";
					instancenumber=l*10+i;
				}
				else so<<"o"<<instancenumber<<".txt";
				vsolutions[i][max].referenceRate=job.minhistory.back();
				vsolutions[i][max].InitSave(so.str(),instancenumber);
				vsolutions[i][max].Rate();
				vsolutions[i][max].deactiveSave();
			}
		}
		fprintf(plik,"%d,%d\n",100*sum/sum2,length/powt);
	}
	fclose(plik);
	return 0;
}
