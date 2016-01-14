#include "Work.hpp"

Work::Work()
{
  Load ld("dane.txt");
  starting_population=ld.file_data.starting_population;
  survival_amount=ld.file_data.survival_amount;
  mutation_percent=ld.file_data.mutation_percent;
  //mutation_amount=ld.file_data.mutation_amount;
  crossover_percent=ld.file_data.crossover_percent;
  //tournament_groupsize=ld.file_data.tournament_groupsize;
}

Work::Work(int starting_population,int survival_amount,int mutation_percent,int mutation_amount,int crossover_percent,int tournament_groupsize,int change_check_distance)
{
  this->starting_population=starting_population;
  this->survival_amount=survival_amount;
  this->mutation_percent=mutation_percent;
  this->mutation_amount=mutation_amount;
  this->crossover_percent=crossover_percent;
  this->tournament_groupsize=tournament_groupsize;
  this->change_check_distance=change_check_distance;
}

void Work::Start(std::vector<Solution> s,int Duration)
{
  solutions=s;
  MainLoop(Duration);
}

void Work::Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration)
{
    Generate(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,Duration);
    MainLoop(Duration);
}

void Work::Generate(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration)
{
    Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,starting_population);
    solutions=gen.GenerateSolution();
}

void Work::MainLoop(int Duration)
{
    minhistory.push_back(solutions[0].getRate());
    for (int i=0;i<solutions.size();i++)
    {
      minhistory[0] = solutions[i].getRate() < minhistory[0] ? solutions[i].getRate() : minhistory[0];
    }
    std::clock_t c_end,c_start = std::clock();
    while(1000 * (c_end-c_start) / CLOCKS_PER_SEC<Duration)
    {
        Mutations();
        Crossingover();
        Tournament();
        int min=0;
        for (int i=0;i<solutions.size();i++)
          min = solutions[i].getRate() < solutions[min].getRate() ? i : min;
        minhistory.push_back(solutions[min].getRate());
        c_end = std::clock();
        if (NoChanges())break;
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
    int temp=0;
    for (int i=0;i<solutions.size();i++)
      if (solutions[i].getRate()<solutions[temp].getRate())temp=i;
    tab[i]=true;
    while (i<solutions.size()-1)
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
        if (j!=min)solutions[groups[i][j]].markfordelete=true;
      }
    }
    for (int i=0;i<solutions.size();i++)
    {
      if (solutions.size()==starting_population)break;
      if (solutions[i].markfordelete)solutions.erase(solutions.begin()+i--);
    }
    for (int i=0;i<solutions.size();i++)
      solutions[i].markfordelete=false;
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
      solutions[j].MultiMutate(rand.Rand()%2,mutation_amount);
  }
  rand.Change(0,solutions.size()-1);
  /*if (NoChanges())
  {
    for (int j=0;j<5;j++)
    {
      int i=rand.Rand();
      solutions.insert(solutions.end(),solutions[i]);
      solutions[i].Swap();
    }
  }*/
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

bool Work::NoChanges()
{
  if (minhistory.size()>=change_check_distance)
    if (minhistory[minhistory.size()-1]==minhistory[minhistory.size()-change_check_distance-1]) return true;
  return false;
}
