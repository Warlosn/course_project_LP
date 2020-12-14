#include "pch.h"
#include <iostream>

extern "C"
{
	int __stdcall writed(unsigned  int num)
	{
		std::cout << num << std::endl;
		return 0;
	}
	int __stdcall writes(char* str)
	{
		std::cout << str << std::endl;
		return 0;
	}

	int __stdcall expn(unsigned  int b, unsigned   int a)
	{

		return pow(a, b);

	}

	unsigned _strlen(const char* rhs) 
	{
		int res = 0;
		while (*rhs++) ++res;

		return res;
	}

	int __stdcall comp( char* first,  char* last)
	{ 
	
			unsigned f = _strlen(first);
			unsigned l = _strlen(last);

			if (f == l) return 1;

			return (f < l) ? 0 : 2;
	
	}

	int __stdcall kvadro(unsigned  int b, unsigned   int a)
	{

		return pow(a, (1 / (double)b));

	}
	int __stdcall  sum(unsigned  int b, unsigned   int a)
	{

		return a + b;
	}
}