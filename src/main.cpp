#include"Load.hpp"
#include"Solution.hpp"
using namespace std;
int main(int argc,char** argv)
{
	Load file("dane.txt");
	Task task[5];
	Answer answer[5];
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
	for(int i=0; i<5 ; i++)
	{
	scanf("%d",&y);
	scanf("%d",&z);
	answer[i].mach[0]=y;
	answer[i].mach[1]=z;
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
	Solution solution(task,answer,maintance1,maintance2,5,4,4);
	printf("%d\n",solution.Rate());
	return 0;
}
