#include "base.h"

using namespace std;

void getCacheSize() 
{
	puts("\nInput the number of the cache_1 size(Unit:KB)");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_size;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_size < 1 || i_cache_size >= 262144
			|| (i_cache_size & (~i_cache_size + 1)) != i_cache_size)
	{
		getCacheSize();
	}
	
	puts("\nInput the number of the cache_2 size(Unit:KB)");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_size_2;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_size_2 < 1 || i_cache_size_2 >= 262144
			|| (i_cache_size_2 & (~i_cache_size_2 + 1)) != i_cache_size_2)
	{
		getCacheSize();
	}
}

void getCacheLineSize()
{
	puts("\nInput the number of the cache_1-line size(Unit:Byte)");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_line_size;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_line_size < 1 || i_cache_line_size >= 262144
			|| (i_cache_line_size & (~i_cache_line_size + 1))
					!= i_cache_line_size)
	{
		getCacheLineSize();
	}

	puts("\nInput the number of the cache_2-line size(Unit:Byte)");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_line_size_2;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_line_size_2 < 1 || i_cache_line_size_2 >= 262144
			|| (i_cache_line_size_2 & (~i_cache_line_size_2 + 1))
					!= i_cache_line_size_2)
	{
		getCacheLineSize();
	}
}

void getMappingMethod()
{
	short temp = 0;
	puts("\nInput the method of assoiativity between main memory and cache:");
	puts("\n\t directive_mapped:input 1");
	puts("\n\t set_associative:input 2");
	puts("\n\t full_associative:input 3");
	cin >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	switch (temp)
	{
	case 1:
		t_assoc = direct_mapped;
		break;
	case 2:
		t_assoc = set_associative;
		break;
	case 3:
		t_assoc = full_associative;
		break;
	default:
		getMappingMethod();
	}
}

void getLineCountEachSet()
{
	puts("\nInput the how many lines in each set in cache_1:");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_set;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_set < 1 || i_cache_set >= 262144
			|| (i_cache_set & (~i_cache_set + 1)) != i_cache_set)
	{
		getLineCountEachSet();
	}

	puts("\nInput the how many lines in each set of in cache_2:");
	puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
	cin >> i_cache_set_2;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	if (i_cache_set_2 < 1 || i_cache_set_2 >= 262144
			|| (i_cache_set_2 & (~i_cache_set_2 + 1)) != i_cache_set_2)
	{
		getLineCountEachSet();
	}
}

void getReplacePolicy()
{
	short temp;
	puts("\nInput the replacement policy:");
	puts("\n\t FIFO(First In First Out):input 1");
	puts("\n\t LRU(Least Recently Used):input 2");
	puts("\n\t LFU(Least Frequently Used):input 3");
	puts("\n\t Random:input 4");
	cin >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	switch (temp)
	{
	case 1:
		t_replace = FIFO;
		break;
	case 2:
		t_replace = LRU;
		break;
	case 3:
		t_replace = LFU;
		break;
	case 4:
		t_replace = Random;
		break;
	default:
		getReplacePolicy();
	}
}

void getWritePolicy()
{
	short temp;
	puts("\nInput write policy:");
	puts("\n\t Write through:input 1");
	puts("\n\t Write back:input 2");
	cin >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
	}
	switch (temp)
	{
	case 1:
		t_write = write_through;
		break;
	case 2:
		t_write = write_back;
		break;
	default:
		getWritePolicy();
	}
}

void getCostOfTime()
{
	puts("\nInput the cost of reading from cache_1:");
	cin>>cost_of_cache_1;
	puts("\nInput the cost of reading from cache_2:");
	cin>>cost_of_cache_2;
	puts("\nInput the cost of reading from main memory:");
	cin>>cost_of_memory;
}

void GetInput(void)
{
	getCacheSize();
	getCacheLineSize();
	getMappingMethod();
	if (t_assoc == direct_mapped) //If the associativity_way is direct_mapped,the replacement polacy can be none only;
	{
		t_replace = none;
		getWritePolicy();
	}
	else if (t_assoc == full_associative)
	{
		getReplacePolicy();
		getWritePolicy();
	}
	else if (t_assoc == set_associative)
	{
		getLineCountEachSet();
		getReplacePolicy();
		getWritePolicy();
	}
	getCostOfTime();
}
