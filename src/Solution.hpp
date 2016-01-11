#pragma once
#include <cstdio>
#include <cstring>
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
		void Crossover(Solution &parent,Solution &crossovered);
		Solution operator=(Solution &from);
		Solution();

		Solution(Task *task,Answer *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size);
		~Solution();
	protected:
		int created = 0;
//		Solution operator=(Solution from);
};
