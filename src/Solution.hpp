#pragma once
#include <cstdio>
#include "Struct.hpp"
class Solution
{
	public:
		int size;
		Task *task = nullptr;
		Maintance *maintance[2] = {nullptr,nullptr};
		int gap_amount[2];
		Answer *answer = nullptr;
		int rate=0;
		int Rate();

		Solution(Task *task,Answer *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size);
		~Solution();
	protected:
		int created = 0;
		Solution Crossover(Solution parent);
//		Solution operator=(Solution from);
};
