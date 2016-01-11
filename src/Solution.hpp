#pragma once
#include <cstdio>
#include <cstring>
#include "Struct.hpp"
#include "Random.hpp"
class Solution
{
	public:
		Task *task = nullptr;
		Maintance *maintance[2] = {nullptr,nullptr};
		int gap_amount[2];
		int getRate();//odwołuje się do zapisane wartości
		int Rate();//zapisuje wartość w rate
		void Crossover(Solution &parent,Solution &crossovered);//wylicza wartość nowo stworzonej odpowiedzi
		Solution operator=(Solution &from);
		Solution();
		void Mutate(Solution &solution,int machine);
		void MultiMutate(Solution &solution,int machine,int MutationAmount);
		Solution* Tournament(Solution *solution_table, int amount);//chyba lepiej bedzie to zrobic poza klasa

		Solution(Task *task,Answer *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size);
		~Solution();
	protected:
		int size;
		Random linearRandom; 
		int rate=0;
		Answer *answer = nullptr;
		int created = 0;
//		Solution operator=(Solution from);
};
