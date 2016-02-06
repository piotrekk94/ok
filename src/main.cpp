#include <vector>
#include <string>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	int j=0,k=1,l=0;
	FILE* plik;
	plik=fopen("test.csv","w");
	//////////////////////////////
	int MaxLength=25000;
	int MaintanceBreaks=250;
	int MaintanceBreaksAvgLength=5;
	int Tasks=500;
	int TasksAvgLength=50;
	int starting_population=100;
	int Duration=50000;
	//////////////////////////////
	int survival_amount=100;
	int change_check_distance=100;
	int mutation_percent=30;
	int crossover_percent=70;
	int mutation_amount=1;
	int tournament_groupsize=3;
	//////////////////////////////
	Instance inst;
	int temp;
	int instancenumber;
	int sum=0;
	int sum2=0;
	int powt=10;
	int length=0;
	std::clock_t c_end,c_start;
	int t=0;
	bool roulette=false,load=false,save=false,randanswer=false,params=false,savebest=false,autotest=false;

	printf("Przeprowadzic wszystkie testy automatycznie ? 1 - tak 0 - nie\n");
	scanf("%d",&temp );
	autotest=temp;

	if (!autotest){
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

	//printf("Ilosc powtorzen:%d\n",powt);
	//scanf("%d",&powt );

	if (!autotest)powt=1;
	while(l<6){
		if (autotest){
			switch (l) {
				case 0:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=50;
					Tasks=500;
					TasksAvgLength=25;
					break;
				case 1:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=50;
					Tasks=50;
					TasksAvgLength=250;
					break;
				case 2:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=5;
					Tasks=500;
					TasksAvgLength=50;
					break;
				case 3:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=5;
					Tasks=500;
					TasksAvgLength=50;
					break;
				case 4:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=5;
					Tasks=500;
					TasksAvgLength=50;
					break;
				case 5:
					MaintanceBreaks=250;
					MaintanceBreaksAvgLength=5;
					Tasks=500;
					TasksAvgLength=50;
					break;
			}
			fprintf(plik,"%d,%d\n",l,k);
			l++;
		}
		else l=6;
		if (load)
		{
			Solution temp;
			std::stringstream si;
			si<<"i"<<instancenumber<<".txt";
			inst=temp.Load_Instance((si.str()).c_str());
			Tasks=inst.task.size();
			MaintanceBreaks=inst.maintance.size();
		}
		std::vector< std::vector<Solution> >	vsolutions;
		if (autotest){
			for (int n=0;n<10;n++){
				Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
				std::vector<Solution> solutions=gen.GenerateSolution();
				vsolutions.push_back(solutions);
			}
		}
		else if (load){
				Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
				gen.ReplaceBreaks(inst);
				gen.ReplaceTasks(inst);
				std::vector<Solution> solutions=gen.GenerateSolution();
				vsolutions.push_back(solutions);
		}
		if (save)
		{
			if (autotest)
				for (int h=0;h<vsolutions.size();h++){
					std::stringstream so;
					so<<"i"<<(l-1)<<h<<".txt";
					vsolutions[h][0].Save_Instance((so.str()).c_str(),(l-1)*10+h);
				}
			else {
				std::stringstream so;
				so<<"i"<<instancenumber<<".txt";
				vsolutions[0][0].Save_Instance((so.str()).c_str(),instancenumber);
			}
		}
		while(j<5){
			if (autotest){
				switch (j) {
					case 0:
						survival_amount=k*10;
						break;
					case 1:
						change_check_distance=k*10;
						break;
					case 2:
						mutation_percent=k*5;
						crossover_percent=100-mutation_percent;
						break;
					case 3:
						mutation_amount=k;
						break;
					case 4:
						tournament_groupsize=k;
						break;
				}
				fprintf(plik,"%d,%d,%d\n",l,j,k);
				printf("%d,%d,%d\n",l,j,k);
				k++;
				if (k==21){
					j++;
					k=1;
				}
			}
			else j=5;
			for(int i=0;i<powt;i++)
			{
				Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,change_check_distance,randanswer,roulette);
				c_start=std::clock();
				job.Start(vsolutions[i],Duration);
				c_end=std::clock();
				sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
				sum2+=job.minhistory[0];
				length+=job.minhistory.size();
				t+=1000*(c_end-c_start)/CLOCKS_PER_SEC;
				if (savebest){
					int max=0;
					for (int l=0;l<vsolutions[i].size();l++)
						max = vsolutions[i][l].getRate() < vsolutions[i][max].getRate() ? l : max;
					std::stringstream so;
					if (autotest){
						so<<"o"<<(l-1)<<i<<j<<k-1<<".txt";
						instancenumber=(l-1)*1000+i*100+j*10+k-1;
					}
					else so<<"o"<<instancenumber<<".txt";
					vsolutions[i][max].InitSave(so.str(),instancenumber);
					vsolutions[i][max].referenceRate=job.minhistory[0];
					vsolutions[i][max].Rate();
				}
			}
			fprintf(plik,"%d,%d,%d\n",100*sum/sum2,length/powt,t/powt);
		}
	}
	fclose(plik);
	return 0;
}
