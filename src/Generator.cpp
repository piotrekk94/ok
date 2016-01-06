#include "Generator.hpp"

Generator::Generator(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength)
{
	this->MaxLength=MaxLength;
	this->MaintanceBreaks=MaintanceBreaks;
	this->MaintanceBreaksAvgLength=MaintanceBreaksAvgLength;
	this->Tasks=Tasks;
	this->TasksAvgLength=TasksAvgLength;
	this->task=new Task[Tasks];
	this->answer=new Answer[Tasks];
	this->maint[0]=new Maintance[MaintanceBreaks];
	this->maint[1]=new Maintance[MaintanceBreaks];
	srand(time(NULL));
}
void Generator::GenerateInstance()
{
	GenerateMaintanceBreaks();
	GenerateTasks();
	GenerateAnswers();
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
void Generator::GenerateAnswers()
{
        int i=0,j=0,k;
        int *tab=new int[Tasks];//tablica z informacja ktore zadania juz sa uporzadkowane 0-nie uporzadkowane 1-zadanie pierwsze uporzadkowane 2-uporzadkowane
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
}
Solution Generator::GenerateSolution()
{
	GenerateAnswers();
	Solution solution(task,answer,maint[0],maint[1],Tasks,MaintanceBreaks,MaintanceBreaks);
	return solution;
}
void Generator::GenerateMaintanceBreaks()
{
	bool ok=false;
	for (int i=0;i<MaintanceBreaks;i++)
	{
		while(!ok)
		{
		maint[0][i].start=rand()%MaxLength;
		maint[0][i].length=MaintanceBreaksAvgLength*(1-MAX_DEVIATION_FROM_AVG)+rand()%int(2*MAX_DEVIATION_FROM_AVG*MaintanceBreaksAvgLength);
		for (int j=0;j<i;j++)
		{
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
