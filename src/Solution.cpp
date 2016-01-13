#include"Solution.hpp"
#define DEBUG 0
//Solution::Solution(int size)
//
int Solution::BasicCheck()
{
	Answer check[size];
	for(int i=0; i<size ; i++)
	{
		check[i].mach[0]=0;
		check[i].mach[1]=0;
	}
	for(int i=0; i<size ; i++)
	{
		++(check[answer[i].mach[0]].mach[0]);
		++(check[answer[i].mach[1]].mach[1]);
	}
	for(int i=0; i<size ; i++)
	{
		if ((check[answer[i].mach[0]].mach[0]) != 1)
		{
			if (DEBUG) printf("Solution::BasicCheck error\n");
			return 1;
		}
		if ((check[answer[i].mach[1]].mach[1]) != 1)
		{
			if (DEBUG) printf("Solution::BasicCheck error\n");
			return 1;
		}
	}
	return 0;
}
int Solution::Rate()
{
	Answer time[size];
	int machine[2]={0,0};
	int mach_wait[2]={0,0};
	int gap[2]={0,0};
	int op1;
	int par=0; //użwyane przy naprawie
	for(int i=0; i<size ; i++)
	{
		time[i].mach[0] = 0;
		time[i].mach[1] = 0;
	}
	if (BasicCheck())
	{
		int d;
		printf("stop\n");
		scanf("%d\n",d );
		return -1;
	}
	if (DEBUG)
	{
		for(int i=0; i<size ; i++)
		{
			printf("%d\t%d\t%d\n",task[i].op[0],task[i].op[1],task[i].machine);
		}
		for(int i=0; i<size ; i++)
		{
			printf("%d\t%d\n",answer[i].mach[0],answer[i].mach[1]);
		}
	}
	{
		int i=0;
		int j=0;
		while((i < size) || (j < size))
		{
			if (DEBUG == 2)
			{
				for(int k=0; k<size ; k++)
				{
					printf("%d\t%d\n",time[k].mach[0],time[k].mach[1]);
				}
			}
			if (DEBUG == 2) printf("Solution::Rate i = %d\n",i);
			if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[0] \n");
			if (answer[i].mach[0] == -1)//czekanie do kolejnej przerwy
			{
				if (gap[0] < gap_amount[0])
				{
					if (machine[0] > maintance[0][gap[0]].start)
					{
						if (DEBUG) printf("Solution::Rate error waiting to past event on machine[0]\n");
					}
					else
					{
						machine[0] = maintance[0][gap[0]].end();
						gap[0]++;
					}
				}
			}
			else if ((i<size) && ((task[answer[i].mach[0]].machine == 0) || (time[answer[i].mach[0]].mach[1] > 0)))//mozliwy blad
				//nie mamy op2 lub odpowiadajace op1 wykonało się umożliwiając wykonanie op2
				//czas zakonczenia op1 nie jest na razie wazny pozniej go sprawdzamy i w razie czego czekamy
			{
				if (machine[0] < time[answer[i].mach[0]].mach[1])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
				{//w tym czasie nic nie robilismy
					machine[0] = time[answer[i].mach[0]].mach[1];//czekamy
					while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) <= machine[0])) gap[0]++;//pomijamy te przerwy ktore minely gdzy czekalismy
					if ((gap[0] > 0) && (maintance[0][gap[0]-1].end() > machine[0])) machine[0] = maintance[0][gap[0]-1].end();//moglibysmy zaczac gdyby nie przerwa techniczna
				}
				machine[0] += task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]; //op1 czy op2
				if ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) < machine[0])) machine[0]+=(task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]+3)*3/10;//kara za przerwanie zadania
				while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) < machine[0]))
				{
					machine[0] += maintance[0][gap[0]++].length;  //liczenie przerw technicznych
				}
				time[answer[i].mach[0]].mach[0] = machine[0];//czas konca
				if ((gap[0] < gap_amount[0]) && (maintance[0][gap[0]].start == machine[0]) && (i != (size-1))) machine[0]+= maintance[0][gap[0]++].length;
				i++;
				mach_wait[0] = 0;
				if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[0] zakończona\n");
			}
			else mach_wait[0] = 1;
			if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[0] \n");
			if (DEBUG == 2) printf("Solution::Rate j = %d\n",j);
			if (answer[i].mach[1] == -1)
			{
				if (gap[1] < gap_amount[1])
				{
					if (machine[1] > maintance[1][gap[1]].start)
					{
						if (DEBUG) printf("Solution::Rate error waiting to past event on machine[1]\n");
					}
					else
					{
						machine[1] = maintance[1][gap[1]].end();
						gap[1]++;
					}
				}
			}
			else if ((j < size) && ((task[answer[j].mach[1]].machine == 1) || (time[answer[j].mach[1]].mach[0] > 0)))//mozliwy blad
				//
				//nie mamy op2 lub op1 wykonało się
			{
				if (machine[1] < time[answer[j].mach[1]].mach[0])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
				{//w tym czasie nic nie robilismy
					machine[1] = time[answer[j].mach[1]].mach[0];
					while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) <= machine[1])) gap[1]++;
					if ((gap[1] > 0) && (maintance[1][gap[1]-1].end() > machine[1])) machine[1] = maintance[1][gap[1]-1].end();//moglibysmy zaczac gdyby nie przerwa techniczna
				}
				machine[1] += task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine];
				//liczenie przerw technicznych
				if ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) < machine[1])) machine[1]+=(task[answer[j].mach[2]].op[1-task[answer[j].mach[1]].machine]+3)*3/10;
				while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) < machine[1]))
				{
					machine[1] += maintance[1][gap[1]++].length; //liczenie przerw technicznych
				}
				time[answer[j].mach[1]].mach[1] = machine[1];//czas konca
				if ((gap[1] < gap_amount[1]) && (maintance[1][gap[1]].start == machine[1]) && (j != (size -1))) machine[1]+= maintance[1][gap[1]++].length;
				j++;
				mach_wait[1] = 0;
				if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[1] zakończona\n");
			}
			else mach_wait[1] = 1;
			if ((mach_wait[0] & mach_wait[1]) == 1) //obie maszyny oczekują na wykonanie op1 trzeba naprawić odpowiedź poprzez przeniesienie jednego z op2 na koniec
			{	//////////////////////////////////////////////////////////////////
				if (DEBUG) printf("Solution::Rate próba naprawienia odpowiedzi\n");
				//par=1-par;//zamieniał na różnych maszynach niepotrzebne teraz tylko na drugiej
				//if (( i < size) && (par == 0))
				//				  {
				//				  int temp = answer[i].mach[0]; //
				//				  for(int k = i; k < (size-1); k++)
				//				  {
				//				  answer[k].mach[0]=answer[k+1].mach[0];
				//				  }
				//				  answer[size-1].mach[0]=temp;
				//				  }
				//else if (j < size)
				{
					int temp = answer[j].mach[1]; //
					for(int k = j; k < (size-1); k++)
					{
						answer[k].mach[1]=answer[k+1].mach[1];
					}
					answer[size-1].mach[1]=temp;
				}
				if (DEBUG==2)
				{
					for(int k=0; k<size ; k++)
					{
						printf("%d\t%d\n",answer[k].mach[0],answer[k].mach[1]);
					}
				}
				if (DEBUG) printf("Solution::Rate próba naprawienia odpowiedzi zakończona\n");
			}
		}
	}
	if (DEBUG)
	{
		printf("czasy poszczegolnych operacji op1 zakonczenia op2 zakonczenia\n");
		for(int i=0; i<size ; i++)
		{
			printf("%d\t%d\n",time[i].mach[0],time[i].mach[1]);
		}
		printf("czas pracy maszyn%d\t%d\n",machine[0],machine[1]);
		printf("answer\n");
		for(int i=0; i<size ; i++)
		{
			printf("%d\t%d\n",answer[i].mach[0],answer[i].mach[1]);
		}
	}
	if ((mach_wait[0] & mach_wait[1]) == 1) return -1;
	//for(int i=0; i<size ; i++) if (time[i].mach[0] > (time[i].mach[1] - task[i].op[1])) return i*-1;
	if (machine[0] > machine[1])
	{
		rate = machine[0];
		return machine[0];
	}
	rate = machine[1];
	return machine[1];
}
Solution::Solution() : linearRandom(new Random)
{
	this->task=nullptr;
	this->size=0;
	this->maintance[0]=nullptr;
	this->maintance[1]=nullptr;
	this->gap_amount[0]=0;
	this->gap_amount[1]=0;
	(*linearRandom).Change(0,size-1);

}
/*
   Solution& Solution::operator=(Solution &from)
   {
   this->task=from.task;
   this->size=from.size;
   this->maintance[0]=from.maintance[0];
   this->maintance[1]=from.maintance[1];
   this->gap_amount[0]=from.gap_amount[0];
   this->gap_amount[1]=from.gap_amount[1];
   this->answer=from.answer;
   linearRandom.Change(0,size-1);
   return *this;
   }
 */
Solution::Solution(Task *task,std::vector<Answer> *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size) : linearRandom(new Random)

{
	this->task=task;
	this->size=task_size;
	this->maintance[0]=maintance1;
	this->maintance[1]=maintance2;
	this->gap_amount[0]=maintance1_size;
	this->gap_amount[1]=maintance2_size;
	this->answer=*answer;
	(*linearRandom).Change(0,size-1);
	Rate();
}
/*
   Solution::~Solution()
   {
   if (DEBUG) printf("elo from destructor\n");
   }
 */
void Solution::Mutate(int machine)
{
	if (DEBUG==2) printf("Solution::Mutate\n");
	int a= (*linearRandom).Rand();
	int b= (*linearRandom).Rand();
	if (DEBUG)
	{
		if ((a>size) || (b>size)) printf("a lub b za duże a:%d b:%d size:%d\n",a,b,size);
	}
	int temp;
	temp = answer[a].mach[machine];
	answer[a].mach[machine] = answer[b].mach[machine];
	answer[b].mach[machine] = temp;
	//Rate();
}
void Solution::MultiMutate(int machine,int MutationAmount)
{
	for(int i=0; i<MutationAmount ; i++)
	{
		Mutate(machine);
	}
}
Solution* Solution::Tournament(Solution *solution_table, int amount)//chyba lepiej bedzie to zrobic poza klasa
{
	Solution *winner;
	for(int i=0; i <amount ; i++)
	{
		winner=solution_table;
		if (winner->rate < solution_table[i].rate) winner=&(solution_table[i]);
	}
	return (winner);

}
void Solution::Crossover(Solution &parent,Solution &crossovered)
{
	//	Solution crossovered;
	//	Solution crossovered(task,nullptr,maintance[0],maintance[1],size,gap_amount[0],gap_amount[1]);
	crossovered=parent;
	int half = size/2;
	int j=0;
	int k=0;
	for (int i=0; i < size ; i++)
	{
		if (this->answer[i].mach[0] < half)
		{
			crossovered.answer[j++].mach[0]=this->answer[i].mach[0];
		}
		if (this->answer[i].mach[1] < half)
		{
			crossovered.answer[k++].mach[1]=this->answer[i].mach[1];
		}
	}
	for (int i=0; i < size ; i++)
	{
		if (parent.answer[i].mach[0] >= half)
		{
			crossovered.answer[j++].mach[0]=parent.answer[i].mach[0];
		}
		if (parent.answer[i].mach[1] >= half)
		{
			crossovered.answer[k++].mach[1]=parent.answer[i].mach[1];
		}
	}

	crossovered.Rate();

}
int Solution::getRate()
{
	return rate;
}
void Solution::PrintAnswers()
{
	for(int i=0; i<size ; i++)
		printf("%d\t%d\n",answer[i].mach[0],answer[i].mach[1]);
}
