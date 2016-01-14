#pragma once
#include "Solution.hpp"
#include "Generator.hpp"
#include "Load.hpp"
#include "Random.hpp"
#include <cstdio>
#include <cstdlib>

class Work
{
public:
    Work();
    Work(int starting_population,int survival_amount,int mutation_percent,int mutation_amount,int crossover_percent,int tournament_groupsize);
    void Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration);
    void Start(std::vector<Solution> solutions,int Duration);
    std::vector<int> minhistory;
private:
    void MainLoop(int Duration);
    void Tournament();
    void Mutations();
    void Crossingover();
    void Generate(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration);
    std::vector<Solution> solutions;
    int starting_population;
    int survival_amount;
    int mutation_percent;
    int mutation_amount;
    int crossover_percent;
    int tournament_groupsize;
};
