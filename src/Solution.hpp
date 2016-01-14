#pragma once
#include <cstdio>
#include <cstring>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include "Struct.hpp"
#include "Random.hpp"
class Solution
{
	public:
	 	bool markfordelete=false;
		Task *task = nullptr;
		Maintance *maintance[2] = {nullptr,nullptr};
		int gap_amount[2];
		int getRate();//odwołuje się do zapisane wartości
		void InitSave(std::string file_name);

		int Rate();//zapisuje wartość w rate
		void Swap();
		void PrintAnswers();
		std::string Print(std::string type,int count,int op, int start,int length, int real_length,int machine);
		void SaveAnswer(std::string M1,std::string M2,Answer idle,int idlec0,int idlec1,int gap0,int gap1);
		void Crossover(Solution &parent,Solution &crossovered);//wylicza wartość nowo stworzonej odpowiedzi
	//	Solution& operator=(Solution &from);
		void Mutate(int machine);
		void MultiMutate(int machine,int MutationAmount);
		Solution* Tournament(Solution *solution_table, int amount);//chyba lepiej bedzie to zrobic poza klasa
		int BasicCheck();
		Solution();
		Solution(Task *task,std::vector<Answer> *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size);
		Solution(Task *task,Answer *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size){};
		/////////////////////////////////////////////

		Instance Load_Instance(const char * file_name);
		void Save_Instance(const char * file_name,int instanceNumber);
		/////////////////////////////////////////////
	protected:
		bool save=false;
		std::string file_name;
		int size;
		std::shared_ptr<Random> linearRandom;
		int rate=0;
		std::vector<Answer> answer;
		int created = 0;
};
