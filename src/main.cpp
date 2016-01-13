#include <vector>
#include "Work.hpp"
using namespace std;
int main(int argc,char** argv)
{
	for(int i=0;i<10;i++)
	{
		Work job(false,100,20,30,70,4);
		job.Start(150,2,20,50,10,2);
	}
	return 0;
}
