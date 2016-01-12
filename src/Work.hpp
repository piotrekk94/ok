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
    void Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration);
private:
    std::vector<Solution> solutions;
    void MainLoop(int Duration);
    void Tournament();
    void Mutations();
    void Crossingover();
    int starting_population;
    int survival_amount;
    int mutation_percent;
    int crossover_percent;
    int tournament_groupsize;
};