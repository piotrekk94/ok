#include"Solution.hpp"
//Solution::Solution(int size)
int Solution::Rate()
{
	Answer time[size];
	int machine[2];
	machine[0]=0;
	machine[1]=0;
	int mach_wait[2]={0,0};
	int gap[2]={0,0};
	int op1;
	for(int i=0; i<size ; i++) 
	{
	time[i].mach[0] = 0;
	time[i].mach[1] = 0;
	}
	for(int i=0; i<size ; i++)
	{
	printf("%d\t%d\t%d\n",task[i].op[0],task[i].op[1],task[i].machine);
	}
	for(int i=0; i<size ; i++)
	{
	printf("%d\t%d\n",answer[i].mach[0],answer[i].mach[1]);
	}
	{
		int i=0;
		int j=0;
		while((i < size) || (j < size)) 
		{
			if ((task[answer[i].mach[0]].machine == 0) || (time[answer[i].mach[0]].mach[0] > 0)) //nie mamy op2 lub op1 wykonało się
			{
				if (i < size)
				{
					if (machine[0] < time[answer[i].mach[0]].mach[0])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
					{//w tym czasie nic nie robilismy
						machine[0] = time[answer[i].mach[0]].mach[0];
						while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) <= machine[0])) gap[0]++;
						if ((gap[1] > 0) && (maintance[0][gap[0]-1].end() > machine[0])) machine[0] = maintance[0][gap[0]-1].end();
					}
					machine[0] += task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]; 
					while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) <= machine[0]))
					{
						machine[0] += maintance[0][gap[0]++].length + (task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]+3)*3/10; //liczenie przerw technicznych
					}
					time[answer[i].mach[0]].mach[task[answer[i].mach[0]].machine] = machine[0];//czas konca
					if ((gap[0] < gap_amount[0]) && (maintance[0][gap[0]].start == machine[0])) machine[0]+= maintance[0][gap[0]++].length;
					i++;
				}
			mach_wait[0] = 0;
			}
			else mach_wait[0] = 1;
			if ((task[answer[j].mach[1]].machine == 1) || (time[answer[j].mach[1]].mach[0] > 0))//nie mamy op2 lub op1 wykonało się
			{
				if (j < size)
				{
					if (machine[1] < time[answer[j].mach[1]].mach[0])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
					{//w tym czasie nic nie robilismy
						machine[1] = time[answer[j].mach[1]].mach[0];
						while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) <= machine[1])) gap[1]++;
						if ((gap[1] > 0) && (maintance[1][gap[1]-1].end() > machine[1])) machine[1] = maintance[1][gap[1]-1].end();//moglibysmy zaczac gdyby nie przerwa techniczna
					}
					machine[1] += task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine];
					//liczenie przerw technicznych
					while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) < machine[1]))
					{
						machine[1] += maintance[1][gap[1]++].length + (task[answer[j].mach[2]].op[1-task[answer[j].mach[1]].machine]+3)*3/10; //liczenie przerw technicznych
					}
					time[answer[j].mach[1]].mach[1-task[answer[j].mach[1]].machine] = machine[1];//czas konca 
					if ((gap[1] < gap_amount[1]) && (maintance[1][gap[1]].start == machine[1])) machine[1]+= maintance[1][gap[1]++].length;
					j++;
				}
			mach_wait[1] = 0;
			}
			else mach_wait[1] = 1; 
			if ((mach_wait[0] & mach_wait[1]) == 1) break;
		}
	}
	//na tym etapie mamy czasy startu operacji2 i konca operacji1
	//operacja1 musi konczyc sie przed rozpoczeciem operacji2
	printf("czasy poszczegolnych operacji op1 zakonczenia op2 zakonczenia\n");
	for(int i=0; i<size ; i++)
	{
		printf("%d\t%d\n",time[i].mach[0],time[i].mach[1]);
	}
	printf("czas pracy maszyn%d\t%d\n",machine[0],machine[1]);
	if ((mach_wait[0] & mach_wait[1]) == 1) return -1;
	//for(int i=0; i<size ; i++) if (time[i].mach[0] > (time[i].mach[1] - task[i].op[1])) return i*-1;
	if (machine[0] > machine[1]) return machine[0];
	return machine[1];
}
Solution::Solution(Task *task,Answer *answer,Maintance * maintance1,Maintance * maintance2,int task_size,int maintance1_size,int maintance2_size)
{
	this->task=task;
	this->size=task_size;
	this->maintance[0]=maintance1;
	this->maintance[1]=maintance2;
	this->gap_amount[0]=maintance1_size;
	this->gap_amount[1]=maintance2_size;
	if (answer != nullptr) this->answer=answer;
	else 
	{
		answer = new Answer[task_size];
		created=1;
	}
}
Solution::~Solution()
{
	if (created)
	{
		delete[] answer;
	}
}
