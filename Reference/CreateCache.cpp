#include "base.h"

using namespace std;

void CreateCache()
{
    temp = i_num_line;
	temp_2 = i_num_line_2;
#ifndef NDEBUG

    for(i=0; i<100; i++)
    {
        cout << cache_item[i] << endl;
    }

#endif // NDEBUG

    for(i=0; i<temp; i++)
    {
        cache_item[i][31] = true;             //valid-bit
    }

	for(i=0; i<temp_2; i++)
    {
        cache_item_2[i][31] = true;             //valid-bit
    }

#ifndef NDEBUG

    for(i=0; i<100; i++)
    {
        cout << cache_item[i] << endl;
    }

#endif // NDEBUG
}
