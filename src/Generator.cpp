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
}

void Generator::ReplaceBreaks(Instance i)
{
    for (int j=0;j<i.maintance.size();j++){
        this->maint[1][j].length=i.maintance[j].length;
        this->maint[1][j].start=i.maintance[j].start;
    }
}
void Generator::ReplaceTasks(Instance i)
{
    for (int j=0;j<i.task.size();j++){
        this->task->machine=i.task[j].machine;
        this->task->op[0]=i.task[j].op[0];
        this->task->op[1]=i.task[j].op[1];
    }
}

void Generator::GenerateInstance()
{
	GenerateMaintanceBreaks();
	GenerateTasks();
}
void Generator::GenerateTasks()
{
	Random op(TasksAvgLength*(1-MAX_DEVIATION_FROM_AVG),TasksAvgLength*(1+MAX_DEVIATION_FROM_AVG),1);
	for(int i=0;i<Tasks;i++)
		{
			task[i].machine=rand()%2;
			task[i].op[0]=op.Rand();
			task[i].op[1]=op.Rand();
		}
}

std::vector<Answer> Generator::GenerateAnswers()
{
        Answer temp;
        std::vector<Answer> answer;
				int **tab=new int*[2];
				tab[0]=new int[Tasks];
				tab[1]=new int[Tasks];
				for (int i=0;i<Tasks;i++){
					tab[0][i]=i;
					tab[1][i]=i;
				}

				std::random_shuffle(&tab[0][0],&tab[0][Tasks]);
				std::random_shuffle(&tab[1][0],&tab[1][Tasks]);

				for (int i=0;i<Tasks;i++)
				{
					temp.mach[0]=tab[0][i];
					temp.mach[1]=tab[1][i];
					answer.push_back(temp);
				}
        return answer;
}
std::vector<Answer> Generator::GenerateAnswersV2()
{
        int i=0,j=0,k;
        int *tab=new int[Tasks];//tablica z informacja ktore zadania juz sa uporzadkowane 0-nie uporzadkowane 1-zadanie pierwsze uporzadkowane 2-uporzadkowane
        for (int i=0;i<Tasks;i++)tab[i]=0;
        Answer temp={.mach={0,0}};
        std::vector<Answer> answer;
        answer.insert(answer.begin(),Tasks,temp);
				Random Rand(0,Tasks-1);
        while(i<Tasks||(j<Tasks))
        {
            k=Rand.Rand();
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
                    answer[k].mach[1]=j;
                    j++;
                    tab[k]++;
                }
                else if (tab[k]==1)
                {
                    answer[k].mach[0]=i;
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
        for (int i=0;i<Population;i++)
        {
            std::vector<Answer> temp=GenerateAnswers();
            Solution sol(task,&temp,maint[0],maint[1],Tasks,0,MaintanceBreaks);
            result.push_back(sol);
        }
	return result;
}

void Generator::GenerateMaintanceBreaks()
{
	Random length(MaintanceBreaksAvgLength*(1-MAX_DEVIATION_FROM_AVG),MaintanceBreaksAvgLength*(1+MAX_DEVIATION_FROM_AVG));
	Random start(0,MaxLength);
	for (int i=0;i<MaintanceBreaks;i++)
	{
		bool ok=false;
		while(!ok)
		{
			maint[1][i].start=start.Rand();
			maint[1][i].length=length.Rand();
    	if (i==0)ok=true;
			for (int j=0;j<i;j++)
			{
				if (maint[1][i].end()<maint[1][j].start||maint[1][i].start>maint[1][j].end())
					ok=true;
				else
				{
					ok=false;
					break;
				}
			}
		}
	}
	std::sort(maint[1],maint[1]+MaintanceBreaks,CompareBreaks);
}

bool CompareBreaks(Maintance const& v1,Maintance const& v2)
{
	if (v1.start<v2.start)return true;
	else return false;
}
