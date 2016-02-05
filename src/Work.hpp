#pragma once
#include "Solution.hpp"
#include "Generator.hpp"
#include "Load.hpp"
#include "Random.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>

class Work
{
public:
    Work(int starting_population,int survival_amount,int mutation_percent,int mutation_amount,int crossover_percent,int tournament_groupsize,int change_check_distance,bool randanswer,bool roulette);
    void Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration);
    void Start(std::vector<Solution> s,int Duration);
    std::vector<int> minhistory;
private:
    void MainLoop(int Duration);
    void Tournament();
    void Roulette();
    void Mutations();
    void Crossingover();
    void Generate(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Duration);
    bool NoChanges(int distance);
    std::vector<Solution> solutions;
    int starting_population;
    int survival_amount;
    int mutation_percent;
    int mutation_amount;
    int crossover_percent;
    int tournament_groupsize;
    int change_check_distance;
    bool randanswer,roulette;
};
