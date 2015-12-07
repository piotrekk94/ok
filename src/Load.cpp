#include "Load.hpp"
Load::Load(const char * file_name)
{
	char stemp[20];
	int itemp;
	int r=1;
	file_data.starting_population=50;
	file_data.survival_amount=50;
	file_data.mutation_percent=30;
	file_data.crossover_percent=70;
	if (sizeof(file_name)>=20) 
	{
		printf("nazwa pliku za dluga:%s\nNastapi wczytanie domyslnych wartosci",file_name);
	}
	else
	{
		strcpy(this->file_name,file_name);
		*(this->file_name +19)='\0';
		file = fopen(file_name,"r");
		if (file == NULL) perror("error plik nie zostal wczytany");
		else
		{
			while (r > 0)
			{
				r = fscanf(file,"%s = %d;\n",stemp,&itemp);
				if (0 == strcmp(stemp,"starting_population")) file_data.starting_population = itemp;
				else if (0 == strcmp(stemp,"survival_amount")) file_data.survival_amount = itemp;
				else if (0 == strcmp(stemp,"mutation_percent")) file_data.mutation_percent = itemp;
				else if (0 == strcmp(stemp,"crossover_percent")) file_data.crossover_percent = itemp;
#if DEBUG 
				else printf("Load::Load  niepoprawna linia:\n");
				printf("Load::Load  %s == %d;\n",stemp,itemp);
#endif
			}
#if DEBUG 
			printf("Load::Load  %d\n",file_data.starting_population);
			printf("Load::Load  %d\n",file_data.survival_amount);
			printf("Load::Load  %d\n",file_data.mutation_percent);
			printf("Load::Load  %d\n",file_data.crossover_percent);
#endif
			fclose(file);
		}
	}
}
int Load::Read()
{
	char stemp[20];
	int itemp;
	int r=1;
	file = fopen(this->file_name,"r");
	if (file == NULL) perror("error plik nie zostal wczytany");
	else
	{
		while (r > 0)
		{
			r = fscanf(file,"%s = %d;\n",stemp,&itemp);
			if (0 == strcmp(stemp,"starting_population")) file_data.starting_population = itemp;
			else if (0 == strcmp(stemp,"survival_amount")) file_data.survival_amount = itemp;
			else if (0 == strcmp(stemp,"mutation_percent")) file_data.mutation_percent = itemp;
			else if (0 == strcmp(stemp,"crossover_percent")) file_data.crossover_percent = itemp;
#if DEBUG 
			else printf("niepoprawna linia:\n");
			printf("%s == %d;\n",stemp,itemp);
#endif
		}
#if DEBUG 
		printf("%d\n",file_data.starting_population);
		printf("%d\n",file_data.survival_amount);
		printf("%d\n",file_data.mutation_percent);
		printf("%d\n",file_data.crossover_percent);
#endif
		fclose(file);
	}
	return 0;
}
