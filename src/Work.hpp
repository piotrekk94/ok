#pragma once
#include "Solution.hpp"
#include "Generator.hpp"
#include <chrono>
#include <cstdio>
#include <cstdlib>

class Work
{
public:
    Work();
    void Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Population,int Duration);
private:
    std::vector<Solution> solutions;
    void MainLoop(int Duration);
};