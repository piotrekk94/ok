#include "Generator.hpp"

Generator::Generator(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Population)
{
	this->MaxLength=MaxLength;
	this->MaintanceBreaks=MaintanceBreaks;
	this->MaintanceBreaksAvgLength=MaintanceBreaksAvgLength;
	this->Tasks=Tasks;
	this->TasksAvgLength=TasksAvgLength;
	this->task=new Task[Tasks];
	this->maint[0]=new Maintance[MaintanceBreaks];
	this->maint[1]=new Maintance[MaintanceBreaks];
        this->Population=Population;
	srand(time(NULL));
        GenerateInstance();
        printf("Wygenerowano instancje\n");
}
Generator::~Generator()
{
    
}
void Generator::GenerateInstance()
{
	GenerateMaintanceBreaks();
	GenerateTasks();
}
void Generator::GenerateTasks()
{
	for(int i=0;i<Tasks;i++)
		{
			task[i].machine=rand()%2;
			task[i].op[0]=TasksAvgLength*(1-MAX_DEVIATION_FROM_AVG)+rand()%int(2*MAX_DEVIATION_FROM_AVG*TasksAvgLength);
			task[i].op[1]=TasksAvgLength*(1-MAX_DEVIATION_FROM_AVG)+rand()%int(2*MAX_DEVIATION_FROM_AVG*TasksAvgLength);
		}
}
std::vector<Answer> Generator::GenerateAnswers()
{
        int i=0,j=0,k;
        int *tab=new int[Tasks];//tablica z informacja ktore zadania juz sa uporzadkowane 0-nie uporzadkowane 1-zadanie pierwsze uporzadkowane 2-uporzadkowane
        for (int i=0;i<Tasks;i++)tab[i]=0;
        Answer temp={.mach={0,0}};
        std::vector<Answer> answer;
        answer.insert(answer.begin(),Tasks,temp);
        while(i<Tasks&&j<Tasks)
        {
            k=rand()%Tasks;
            if(task[k].machine==0)
            {
                if (tab[k]==0)
                {
                    answer[k].mach[0]=i;
                    i++;
                    tab[k]++;
                }
                else if (tab[k]==1)
                {
                    answer[k].mach[1]=j;
                    j++;
                    tab[k]++;
                }
                
            }
            else if(task[k].machine==1)
            {
                if (tab[k]==0)
                {
                    answer[k].mach[0]=j;
                    j++;
                    tab[k]++;
                }
                else if (tab[k]==1)
                {
                    answer[k].mach[1]=i;
                    i++;
                    tab[k]++;
                }
            }
        }
        delete tab;
        return answer;
}
std::vector<Solution> Generator::GenerateSolution()
{
        std::vector<Solution> result;
        printf("Solucje");
        for (int i=0;i<Population;i++)
        {
            std::vector<Answer> *temp=new std::vector<Answer>;
            *temp=GenerateAnswers();
            Solution sol(task,temp,maint[0],maint[1],Tasks,MaintanceBreaks,MaintanceBreaks);
            result.push_back(sol);
            printf("Wygenerowano %d solucje\n",i);
        }
	return result;
}
void Generator::GenerateMaintanceBreaks()
{
	bool ok=false;
        printf("Przerwy\n");
	for (int i=0;i<MaintanceBreaks;i++)
	{
		while(!ok)
		{
		maint[0][i].start=rand()%MaxLength;
		maint[0][i].length=MaintanceBreaksAvgLength*(1-MAX_DEVIATION_FROM_AVG)+rand()%int(2*MAX_DEVIATION_FROM_AVG*MaintanceBreaksAvgLength);
                if (i==0)ok=true;
		for (int j=0;j<i;j++)
		{
                        printf("%d %d\n",i,j);
			if ((maint[0][i].start<maint[0][j].start&&maint[0][i].end()<maint[0][j].start)||(maint[0][i].start>maint[0][j].end()&&maint[0][i].end()>maint[0][j].end()))
				ok=true;
			else
			{
				ok=false;
				break;
			}
		}
		}
	}
	ok=false;
	for (int i=0;i<MaintanceBreaks;i++)
	{
		while(!ok)
		{
		maint[1][i].start=rand()%MaxLength;
		maint[1][i].length=MaintanceBreaksAvgLength*(1-MAX_DEVIATION_FROM_AVG)+rand()%int(2*MAX_DEVIATION_FROM_AVG*MaintanceBreaksAvgLength);
                if (i==0)ok=true;
		for (int j=0;j<i;j++)
		{
			if ((maint[1][i].start<maint[1][j].start&&maint[1][i].end()<maint[1][j].start)||(maint[1][i].start>maint[1][j].end()&&maint[1][i].end()>maint[1][j].end()))
				ok=true;
			else
			{
				ok=false;
				break;
			}
		}
		}
	}
}
