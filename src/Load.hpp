#pragma once
#include <cstdio>
//#include <string>
#include <cstring>
#define DEBUG 0
using namespace std;
struct File_data
{
	int starting_population;
	int survival_amount;
	int mutation_percent;
	int crossover_percent;
};
class Load
{
	protected:
	FILE *file;
	public:
		File_data file_data;
		char file_name[20];

		int Read();
		Load(const char * file_name);
//		~Load();
};
