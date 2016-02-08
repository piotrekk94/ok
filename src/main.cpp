#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "Work.hpp"
using namespace std;

int main(int argc,char** argv)
{
	int j=0,k=1,l=0;
	FILE* plik;

	int temp,instancenumber,sum=0,sum2=0,powt=10,length=0,t=0;
	std::clock_t c_end,c_start;

	//////////////////////////////
	int MaxLength=3500;
	int MaintanceBreaks=500;
	int MaintanceBreaksAvgLength=2;
	int Tasks=50;
	int TasksAvgLength=50;
	int starting_population=100;
	int Duration=5000;
	//////////////////////////////
	int survival_amount=100;
	int change_check_distance=20;
	int mutation_percent=30;
	int crossover_percent=70;
	int mutation_amount=1;
	int tournament_groupsize=3;
	//////////////////////////////

	std::vector<std::vector<Solution>> vsolutions;
  //plik=fopen("test.csv","w");
	bool roulette=false,load=false,save=false,randanswer=false,params=false,savebest=false,autotest=false;

	for (int n=0;n<10;n++){
		if (argc==2){
			n=argv[1][0]-'0';
			printf("%d\n",n );
		}
    vsolutions.clear();
		switch (n) {
			case 0:
			MaxLength=1000;
			MaintanceBreaks=7;
			MaintanceBreaksAvgLength=40;
			Tasks=75;
			TasksAvgLength=10;
			starting_population=100;
			Duration=1000;
			break;
			case 1:
			MaxLength=1000;
			MaintanceBreaks=37;
			MaintanceBreaksAvgLength=8;
			Tasks=75;
			TasksAvgLength=10;
			starting_population=100;
			Duration=1000;
			break;
			case 2:
			MaxLength=1000;
			MaintanceBreaks=2;
			MaintanceBreaksAvgLength=100;
			Tasks=20;
			TasksAvgLength=40;
			starting_population=100;
			Duration=1000;
			break;
			case 3:
			MaxLength=1000;
			MaintanceBreaks=10;
			MaintanceBreaksAvgLength=20;
			Tasks=20;
			TasksAvgLength=40;
			starting_population=100;
			Duration=1000;
			break;
			case 4:
			MaxLength=1000;
			MaintanceBreaks=100;
			MaintanceBreaksAvgLength=2;
			Tasks=200;
			TasksAvgLength=4;
			starting_population=100;
			Duration=1000;
			break;
			case 5:
			MaxLength=1000;
			MaintanceBreaks=20;
			MaintanceBreaksAvgLength=10;
			Tasks=200;
			TasksAvgLength=4;
			starting_population=100;
			Duration=1000;
			break;
			case 6:
			MaxLength=1000;
			MaintanceBreaks=150;
			MaintanceBreaksAvgLength=2;
			Tasks=150;
			TasksAvgLength=5;
			starting_population=100;
			Duration=1000;
			break;
			case 7:
			MaxLength=1000;
			MaintanceBreaks=300;
			MaintanceBreaksAvgLength=1;
			Tasks=150;
			TasksAvgLength=5;
			starting_population=100;
			Duration=1000;
			break;
			case 8:
			MaxLength=1000;
			MaintanceBreaks=200;
			MaintanceBreaksAvgLength=1;
			Tasks=400;
			TasksAvgLength=2;
			starting_population=100;
			Duration=1000;
			break;
			case 9:
			MaxLength=1000;
			MaintanceBreaks=40;
			MaintanceBreaksAvgLength=5;
			Tasks=400;
			TasksAvgLength=2;
			starting_population=100;
			Duration=1000;
			break;
		}
		std::stringstream testname;
		testname<<"test"<<n<<".csv";
		plik=fopen(testname.str().c_str(),"w");
		for(int i=0; i < powt ; i++)
		{
			Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
			std::vector<Solution> solutions=gen.GenerateSolution();
			vsolutions.push_back(solutions);
			printf("%d\n",i);
			std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
		}
		for(int k=0; k < 10 ; k++)
		{
			mutation_percent = k * 10;
			if (k == 0)
			{
			fprintf(plik,", ");
			for(int j=0; j < 10 ; j++)
				fprintf(plik,"%d,",j * 10);
			fprintf(plik,"\n");
			}
			fprintf(plik,"%d",mutation_percent);
			for(int j=0; j < 10 ; j++)
			{
				crossover_percent = j * 10;
				length = 0;
				sum = 0;
				sum2 = 0;
				t = 0;
				for(int i=0;i<powt;i++)
				{
					printf("starting_population: %d; survival_amount: %d; mutation_percent: %d; crossover_percent: %d;\n",starting_population,survival_amount,mutation_percent,crossover_percent);
					Work job(starting_population,survival_amount,mutation_percent,mutation_amount,crossover_percent,tournament_groupsize,change_check_distance,randanswer,roulette);
					c_start=std::clock();
					job.Start(vsolutions[i],Duration);
					c_end=std::clock();
					sum+=job.minhistory[0]-job.minhistory[job.minhistory.size()-1];
					sum2+=job.minhistory[0];
					length+=job.minhistory.size();
					t+=1000*(c_end-c_start)/CLOCKS_PER_SEC;
				}
				fprintf(plik,",%d",100*sum/sum2 );
			}
			fprintf(plik,"\n");
		}
		fclose(plik);
		if (argc==2)return 0;
	}
	/*
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
		//starting_population=1;
		//Duration/=10;
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
		vsolutions.clear();
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
	fclose(plik);*/
	return 0;
}
