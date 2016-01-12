#include "Work.hpp"

Work::Work()
{
  Load ld("dane.txt");
  starting_population=ld.file_data.starting_population;
  survival_amount=ld.file_data.survival_amount;
  mutation_percent=ld.file_data.mutation_percent;
  crossover_percent=ld.file_data.crossover_percent;
  tournament_groupsize=4;
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
    time(&start);
    time(&end);
    while(end-start<Duration)
    {
        printf("Populacja %d\n",solutions.size());
        Mutations();
        printf("Mutacje\n" );
        Crossingover();
        printf("Krzyzowanie\n" );
        Tournament();
        printf("Turniej\n");
        time(&end);
        printf("Minelo %d\n", end-start);
    }
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
      int max=0;
      int size=groups[i].size();
      for (int j=0;j<size;j++)
        max = solutions[groups[i][j]].getRate() > solutions[groups[i][max]].getRate() ? j : max;
      for (int j=0;j<size;j++)
        if (j!=max)solutions.erase(solutions.begin()+groups[i][j]);
    }
    delete tab;
}

void Work::Mutations()
{
  Random rand(0,solutions.size()-1);
  int size=solutions.size();
  for (int i=0;i<mutation_percent*size;i++)
  {
      int j=rand.Rand();
      solutions.insert(solutions.end(),solutions[j]);
      solutions[j].Mutate(rand.Rand()%2);
  }
}

void Work::Crossingover()
{
  Random rand(0,solutions.size()-1);
  int size=solutions.size();
  for (int i=0;i<crossover_percent*size;i++)
  {
      int j=rand.Rand();
      int k=rand.Rand();
      solutions.insert(solutions.end(),solutions[j]);
      solutions[j].Crossover(solutions[j],solutions[k]);
  }
}
