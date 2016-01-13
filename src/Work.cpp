#include "Work.hpp"

Work::Work(bool fromfile, int starting_population,int survival_amount,int mutation_percent,int crossover_percent,int tournament_groupsize)
{
  if (fromfile)
  {
    Load ld("dane.txt");
    starting_population=ld.file_data.starting_population;
    survival_amount=ld.file_data.survival_amount;
    mutation_percent=ld.file_data.mutation_percent;
    crossover_percent=ld.file_data.crossover_percent;
    //tournament_groupsize=ld.file_data.tournament_groupsize;
  }
  else
  {
    this->starting_population=starting_population;
    this->survival_amount=survival_amount;
    this->mutation_percent=mutation_percent;
    this->crossover_percent=crossover_percent;
    this->tournament_groupsize=tournament_groupsize;
  }

}

void Work::Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration)
{
        Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
        solutions=gen.GenerateSolution();
        MainLoop(Duration);
}

void Work::MainLoop(int Duration)
{
    time_t start,end;
    minhistory.push_back(100000000);
    for (int i=0;i<solutions.size();i++)
    {
      minhistory[0] = solutions[i].getRate() < minhistory[0] ? solutions[i].getRate() : minhistory[0];
      //solutions[i].PrintAnswers();
      //printf("%d\n\n",solutions[i].getRate());
    }
    //scanf("%d\n",&end );
    time(&start);
    time(&end);
    while(end-start<Duration)
    {
        //printf("Populacja %d\n",solutions.size());
        Mutations();
        //printf("Mutacje\n" );
        Crossingover();
        //printf("Krzyzowanie\n" );
        Tournament();
        //printf("Turniej\n");
        time(&end);
        //printf("Minelo %d\n", end-start);
        int min=0;
        for (int i=0;i<solutions.size();i++)
          min = solutions[i].getRate() < solutions[min].getRate() ? i : min;
        minhistory.push_back(solutions[min].getRate());
    }

    printf("%d,%d\n",minhistory[0],minhistory[minhistory.size()-1] );
}
void Work::Tournament()
{
    std::vector<std::vector<int>> groups;
    std::vector<int> group;
    Random rand(0,solutions.size()-1);
    bool *tab = new bool[solutions.size()];
    for (int i=0;i<solutions.size();i++)
        tab[i]=false;
    int i=0,j;
    while (i<solutions.size())
    {
        j=rand.Rand();
        if (!tab[j])
        {
            tab[j]=true;
            if (i%tournament_groupsize==0)
              groups.push_back(group);
            groups[i/tournament_groupsize].push_back(j);
            i++;
        }
    }
    for (int i=0;i<groups.size();i++)
    {
      int min=0;
      int size=groups[i].size();
      for (int j=0;j<size;j++)
        min = solutions[groups[i][j]].getRate() < solutions[groups[i][min]].getRate() ? j : min;
      for (int j=0;j<size;j++)
      {
        if (solutions.size()==starting_population)break;
        if (j!=min)solutions.erase(solutions.begin()+groups[i][j]);
      }
    }
    delete tab;
}

void Work::Mutations()
{
  Random rand(0,solutions.size()-1);
  int size=solutions.size();
  for (int i=0;i<mutation_percent*size/100;i++)
  {
      int j=rand.Rand();
      solutions.insert(solutions.end(),solutions[j]);
      //solutions[j].Mutate(rand.Rand()%2);
      solutions[j].MultiMutate(rand.Rand()%2,5);
  }
}

void Work::Crossingover()
{
  Random rand(0,solutions.size()-1);
  int size=solutions.size();
  for (int i=0;i<crossover_percent*size/100;i++)
  {
      int j=rand.Rand();
      int k=rand.Rand();
      solutions.insert(solutions.end(),solutions[j]);
      solutions[j].Crossover(solutions[k],solutions[solutions.size()-1]);
  }
}
