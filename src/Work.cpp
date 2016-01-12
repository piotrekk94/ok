#include "Work.hpp"

void Work::Start(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Population,int Duration)
{
        Generator gen(MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,Population);
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
        
        time(&end);
    }
}