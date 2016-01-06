#pragma once
#include <cstdio>
#include <cstdlib>
#include "Struct.hpp"
#include "Solution.hpp"
#include "time.h"

#define MAX_DEVIATION_FROM_AVG 0.2

class Generator
{
	public:
		Generator(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength);
		~Generator();
		void GenerateInstance();
		Solution GenerateSolution();
	private:
		Task	  *task;
		Answer	  *answer;
		Maintance *maint[2];
		int MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength;
		void GenerateMaintanceBreaks();
		void GenerateTasks();
		void GenerateAnswers();
};