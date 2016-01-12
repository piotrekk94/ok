#include <vector>
#include"Load.hpp"
#include"Solution.hpp"
using namespace std;
typedef std::vector<Answer> klasa;
int main(int argc,char** argv)
{
//	Load file("dane.txt");
	Task task[5];
	std::vector<Answer> answer;
	std::vector<Answer> answer2;
	Answer tempAnswer;
	Maintance maintance1[4];
	Maintance maintance2[4];
	int x,y,z;
	for(int i=0; i<5 ; i++)
	{
		scanf("%d",&x);
		scanf("%d",&y);
		scanf("%d",&z);
		task[i].op[0]=x;
		task[i].op[1]=y;
		task[i].machine=z;
	}
	for(int i=0; i<4 ; i++)
	{
		scanf("%d",&y);
		scanf("%d",&z);
		maintance1[i].start=y;
		maintance1[i].length=z;
	}
	for(int i=0; i<4 ; i++)
	{
		scanf("%d",&y);
		scanf("%d",&z);
		maintance2[i].start=y;
		maintance2[i].length=z;
	}
	answer.reserve(5);
	for(int i=0; i<5 ; i++)
	{
		scanf("%d",&answer[i].mach[0]);
		scanf("%d",&answer[i].mach[1]);
//		answer.push_back(tempAnswer);
	}
	answer2=answer;
	answer2.~klasa();
	Solution solution(task,&answer,maintance1,maintance2,5,4,4);
	for(int i=0; i<5 ; i++)
	{
		scanf("%d",&y);
		scanf("%d",&z);
		answer[i].mach[0]=y;
		answer[i].mach[1]=z;
	}
//	tempAnswer.~Answer();
//	Solution solution3(task,&answer,maintance1,maintance2,5,4,4);
//	Solution solution2(task,&answer,maintance1,maintance2,5,4,4);
//	Solution solutionr(task,&answer,maintance1,maintance2,5,4,4);
//	Solution solutionc;
//	solution.Crossover(solution2,solutionc);
//	solutionr.~Solution();
//	solution2.answer->mach[0]=0;
//	for(int i=0; i<5 ; i++) printf("%d\t%d\n",solution2.answer[i].mach[0],solution2.answer[i].mach[1]);

//	printf("%d\n",solution.Rate());
//	printf("%d\n",solution2.Rate());
///	printf("stop\n");
//	printf("%d\n",solutionc.Rate());
//	solution.~Solution();
//	printf("stop1\n");
//	solution2.~Solution();
//	printf("stop2\n");
//	solution3.~Solution();
//	printf("stop3\n");
//	solutionc.~Solution();
//	printf("stopc\n");
//	answer.~klasa();
//	printf("stopKLASA\n");
	//file.~Load();
	//printf("stopLOAD\n");
	return 0;
}
