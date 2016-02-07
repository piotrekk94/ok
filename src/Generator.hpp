#pragma once
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "Struct.hpp"
#include "Solution.hpp"
#include "Random.hpp"
#include "time.h"

#define MAX_DEVIATION_FROM_AVG 0.7

class Generator
{
	public:
		Generator(int MaxLength,int MaintanceBreaks,int MaintanceBreaksAvgLength,int Tasks,int TasksAvgLength,int Population);//Przerwa techniczna nie moze sie zaczac dalej niz MaxLength
		void ReplaceBreaks(Instance i);
		void ReplaceTasks(Instance i);
		std::vector<Solution> GenerateSolution();
	private:
		Task *task;
		Maintance *maint[2];
		int MaxLength,MaintanceBreaks,MaintanceBreaksAvgLength,Tasks,TasksAvgLength,Population;
		void GenerateMaintanceBreaks();
		void GenerateTasks();
		std::vector<Answer> GenerateAnswers();
		std::vector<Answer> GenerateAnswersV2();
        std::vector<Task> task;
        std::vector<Maintance> maintance;
    void GenerateInstance();
};

bool CompareBreaks(Maintance const& v1,Maintance const& v2);
