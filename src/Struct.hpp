#pragma once
struct Task
{
	int op[2];
	int machine; //jakie zadanie wykonuje sie na maszynie pierwszej 0 oznacza wykonanie pierwszej operacji na pierwszej maszynie, 1 oznacza wykonanie drugiej operacji na pierwszej maszynie
};
struct Answer
{
	int mach[2];
};
struct Maintance
{
	int start;
	int length;
	int end()
	{
	return start+length;
	}
};
