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
void Solution::InitSave(std::string file_name)
	{
		this->file_name=file_name;
		save=true;
	}
std::string Solution::Print(std::string type,int count,int op, int start,int length, int real_length,int machine)
	{
		if (type == "op")
		{
			std::stringstream stream;
			stream << "o" << op+1 <<"_"<<count<<","<<start<<","<<length<<","<<real_length<<";";
			return stream.str();
		}
		if (type == "idle")
		{
			std::stringstream stream;
			stream << "idle" <<count<<"_M"<< machine+1<<","<<start<<","<<length<<";";
			return stream.str();
		}
		if (type == "maint")
		{
			std::stringstream stream;
			stream << "maint" <<count<<"_M"<< machine+1<<","<<start<<","<<length<<";";
			return stream.str();
		}
	}
void Solution::SaveAnswer(std::string M1,std::string M2,Answer idle,int idlec0,int idlec1,int gap0,int gap1)
{
	int maint0=0,maint1=0;
	for(int i=0;i < gap0 ; i++)
		maint0+=maintance[0][i].length;
	for(int i=0;i < gap1 ; i++)
		maint0+=maintance[1][i].length;
	FILE * file = fopen(file_name.c_str(),"w");
	fprintf(file,"M1: %s\nM2: %s\n%d;%d\n%d;%d\n%d;%d\n%d;%d\n",M1.c_str(),M2.c_str(),gap0,maint0,gap1,maint1,idlec0,idle.mach[0],idlec1,idle.mach[1]);

	fclose(file);
}
int Solution::Rate()
{
	Answer time[size];
	int machine[2]={0,0};
	int mach_wait[2]={0,0};
	int gap[2]={0,0};
	int op1;
	Answer idle_time={0};
	int realtime,start;
	std::string M1,M2;
	int idle,M1IdleCounter=0,M2IdleCounter=0;
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
			if ((i<size) && ((task[answer[i].mach[0]].machine == 0) || (time[answer[i].mach[0]].mach[1] > 0)))//mozliwy blad
				//nie mamy op2 lub odpowiadajace op1 wykonało się umożliwiając wykonanie op2
				//czas zakonczenia op1 nie jest na razie wazny pozniej go sprawdzamy i w razie czego czekamy
			{
				if (machine[0] < time[answer[i].mach[0]].mach[1])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
				{//w tym czasie nic nie robilismy
					if (gap[0]< gap_amount[0]) {idle = (time[answer[i].mach[0]].mach[1] < maintance[0][gap[0]].start ? time[answer[i].mach[0]].mach[1] : maintance[0][gap[0]].start) - machine[0];}
					else idle = time[answer[i].mach[0]].mach[1]- machine[0];
					if (save) M1 += Print("idle",M1IdleCounter++,1,machine[0],idle,idle,0);
					machine[0] = time[answer[i].mach[0]].mach[1];//czekamy
					idle_time.mach[0]+=idle;
					while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) <= machine[0]))
						{//trzeba je wypisac
							if (save) M1 += Print("maint",gap[0],1,maintance[0][gap[0]].start,maintance[0][gap[0]].length,maintance[0][gap[0]].length,0);
							gap[0]++;//pomijamy te przerwy ktore minely gdzy czekalismy
							if ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) <= machine[0]))
								{
									idle = maintance[0][gap[0]].start - maintance[0][gap[0]-1].end();
									if (save) M1 += Print("idle",M1IdleCounter++,1,maintance[0][gap[0]-1].end(),idle,idle,0);
									idle_time.mach[0]+=idle;
								}
						}
					if ((gap[0] > 0) && (maintance[0][gap[0]-1].end() > machine[0])) machine[0] = maintance[0][gap[0]-1].end();//moglibysmy zaczac gdyby nie przerwa techniczna
				}
				start=machine[0];
				machine[0] += task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]; //op1 czy op2
				realtime = task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]; //op1 czy op2
				if ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) < machine[0]))
					{
					machine[0]+=(task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]+3)*3/10;//kara za przerwanie zadania
					realtime += (task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine]+3)*3/10;
					}
			if (save)	M1 += Print("op",answer[i].mach[0],task[answer[i].mach[0]].machine,start,task[answer[i].mach[0]].op[task[answer[i].mach[0]].machine],realtime,0);
				while ((gap[0] < gap_amount[0]) && ((maintance[0][gap[0]].start) < machine[0]))
				{
					machine[0] += maintance[0][gap[0]++].length;  //liczenie przerw technicznych
					if (save)	M1 += Print("maint",gap[0],1,maintance[0][gap[0]].start,maintance[0][gap[0]].length,maintance[0][gap[0]].length,0);
				}
				time[answer[i].mach[0]].mach[0] = machine[0];//czas konca
				if ((gap[0] < gap_amount[0]) && (maintance[0][gap[0]].start == machine[0]) && (i != (size-1)))
					{
			if (save)		M1 += Print("maint",gap[0],1,maintance[0][gap[0]].start,maintance[0][gap[0]].length,maintance[0][gap[0]].length,0);
					machine[0]+= maintance[0][gap[0]++].length;
					}
				i++;
				mach_wait[0] = 0;
				if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[0] zakończona\n");
			}
			else mach_wait[0] = 1;
			if (DEBUG) printf("Solution::Rate próba zliczenia czasu na machine[0] \n");
			if (DEBUG == 2) printf("Solution::Rate j = %d\n",j);
			if ((j < size) && ((task[answer[j].mach[1]].machine == 1) || (time[answer[j].mach[1]].mach[0] > 0)))//mozliwy blad
				//
				//nie mamy op2 lub op1 wykonało się
			{
				if (machine[1] < time[answer[j].mach[1]].mach[0])//co nastapilo pozniej zakonczenie operacji poprzedniej czy powiazanej
				{//w tym czasie nic nie robilismy
					if (gap[1] < gap_amount[1]){ idle = (time[answer[j].mach[1]].mach[0] < maintance[1][gap[1]].start ? time[answer[j].mach[1]].mach[0] : maintance[1][gap[1]].start) - machine[1];}
					else idle = time[answer[j].mach[1]].mach[0] - machine[1];
					if (save) M2 += Print("idle",M2IdleCounter++,1,machine[1],idle,idle,1);
					machine[1] = time[answer[j].mach[1]].mach[0];
					idle_time.mach[1]+=idle;
					while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) <= machine[1]))
						{
							if (save) M2 += Print("maint",gap[1],1,maintance[1][gap[1]].start,maintance[1][gap[1]].length,maintance[1][gap[1]].length,1);
							gap[1]++;//pomijamy te przerwy ktore minely gdzy czekalismy
							if ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) <= machine[1]))
								{
								idle =maintance[1][gap[1]].start - maintance[1][gap[1]-1].end();
								if (save) M2 += Print("idle",M2IdleCounter++,1,maintance[1][gap[1]-1].end(),idle,idle,1);

								idle_time.mach[1]+=idle;
								}

						}
					if ((gap[1] > 0) && (maintance[1][gap[1]-1].end() > machine[1])) machine[1] = maintance[1][gap[1]-1].end();//moglibysmy zaczac gdyby nie przerwa techniczna
				}
				start=machine[1];
				machine[1] += task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine];
				realtime= task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine];
				//liczenie przerw technicznych
				if ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) < machine[1]))
					{
					machine[1]+=(task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine]+3)*3/10;
					realtime+=(task[answer[j].mach[1]].op[1-task[answer[j].mach[1]].machine]+3)*3/10;
					}
				if (save) M2 += Print("op",answer[j].mach[1],task[answer[j].mach[1]].machine,start,task[answer[j].mach[1]].op[task[answer[j].mach[1]].machine],realtime,1);
				while ((gap[1] < gap_amount[1]) && ((maintance[1][gap[1]].start) < machine[1]))
				{
				if (save)	M2 += Print("maint",gap[1],1,maintance[1][gap[1]].start,maintance[1][gap[1]].length,maintance[1][gap[1]].length,1);
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
	if (save) SaveAnswer(M1,M2,idle_time,M1IdleCounter,M2IdleCounter,gap[0],gap[1]);
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
 void Solution::Swap()
 {
	 std::vector<Answer> temp;
	 temp=answer;
	 for(int i=0;i<answer.size();i++)
	 {
		 answer[i].mach[0]=temp[i].mach[1];
		 answer[i].mach[1]=temp[i].mach[0];
	 }
 }
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
}
void Solution::MultiMutate(int machine,int MutationAmount)
{
	for(int i=0; i<MutationAmount ; i++)
	{
		Mutate(machine);
	}
	Rate();
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
	Random Rand(size/5,4*size/5);
	int dividePoint1 = Rand.Rand();
	int dividePoint2 = Rand.Rand();
	int j=0;
	int k=0;
	Answer tab[size];
	for(int i=0; i < size ; i++)
	{
		tab[i].mach[0]=0;
		tab[i].mach[1]=0;
	}
	if (symetricDivide) dividePoint1=dividePoint2;
	for(k=0; k < dividePoint1 ; k++)
	{
		tab[crossovered.answer[k].mach[0]].mach[0]=1;
	}
	for(j=0; j < dividePoint2 ; j++)
	{
		tab[crossovered.answer[j].mach[1]].mach[1]=1;
	}
	for(int i=0; i < size ; i++)
	{
		if (tab[answer[i].mach[0]].mach[0] == 0) crossovered.answer[k++].mach[0]=answer[i].mach[0];
		if (tab[answer[i].mach[1]].mach[1] == 0) crossovered.answer[j++].mach[1]=answer[i].mach[1];
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
//////////////////////////////////
Instance Solution::Load_Instance(const char * file_name)
{
	Instance instance;
	FILE *file = fopen(file_name,"r");
	if (file == nullptr) perror("error plik nie zostal wczytany");
	else
	{
		int taskSize;
		fscanf(file,"**** %d ****\n",&instance.number);
		fscanf(file,"%d\n",&taskSize);
		instance.task.resize(taskSize);
		Maintance temp;
		int limbo;
		for(int i=0; i < taskSize ; i++)
		{
			fscanf(file,"%d;%d;%d;%d;",&instance.task[i].op[0],&instance.task[i].op[1],&instance.task[i].machine,&limbo);
			instance.task[i].machine--;
		}
		int number=-1;
		int check=-1;
		while (number == check)
		{
			check++;
			fscanf(file,"%d;%d;%d\n",&number,&temp.start,&temp.length);
			instance.maintance.push_back(temp);
		}
		fclose(file);
	}

	return instance;
}
void Solution::Save_Instance(const char * file_name,int instanceNumber)
{
	FILE *file = fopen(file_name,"w");
	if (file == NULL) perror("error plik nie zostal wczytany");
	else
	{
		fprintf(file,"**** %d ****\n",instanceNumber);
		fprintf(file,"%d\n",size);
		for(int i=0; i < size ; i++)
		{
			fprintf(file,"%d;%d;%d;%d;\n",task[i].op[0],task[i].op[1],task[i].machine+1, (task[i].machine?0:1) +1);
		}
		for(int i=0; i <gap_amount[1]  ; i++)
			fprintf(file,"%d;%d;%d\n",i,maintance[1][i].start,maintance[1][i].length);
		fprintf(file,"*** EOF ***");
		fclose(file);
	}
}
