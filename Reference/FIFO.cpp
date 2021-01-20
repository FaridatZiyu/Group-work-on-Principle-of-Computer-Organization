#include "base.h"

using namespace std;

void FIFOHitProcess(){};

void FIFOHitProcess_2(){};

void FIFOUnhitSpace()
{
	if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line; i++)
        {
            if(cache_item[current_line][30]==true)
            {
                FIFO_priority[i]++; // 如果该行该行中hit为true
            }
        }

        FIFO_priority[current_line] = 0;
    }
	else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(cache_item[current_line][30]==true)
            {
                FIFO_priority[i]++; // 如果该行该行中hit为true
            }
        }

        FIFO_priority[current_line] = 0;
    }
}

void FIFOUnhitSpace_2()
{
	if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line_2; i++)
        {
            if(cache_item_2[current_line_2][30]==true)
            {
                FIFO_priority_2[i]++; // 如果该行该行中hit为true
            }
        }

        FIFO_priority_2[current_line_2] = 0;
    }
	else if(t_assoc == set_associative)
    {
        for(i=(current_set_2*i_cache_set_2); i<((current_set_2+1)*i_cache_set_2); i++)
        {
            if(cache_item_2[current_line_2][30]==true)
            {
                FIFO_priority_2[i]++; // 如果该行该行中hit为true
            }
        }

        FIFO_priority_2[current_line_2] = 0;
    }
}

void FIFOUnhitUnspace()
{
	if(t_assoc == full_associative)
    {
        temp = FIFO_priority[0];

        for(i=0; i<i_num_line; i++)
        {
            if(FIFO_priority[i]>=temp)
            {
                temp = FIFO_priority[i];
                j = i;
            }
        }

        current_line = j;
    }

	if(t_assoc == set_associative)
    {
        temp = FIFO_priority[current_set*i_cache_set];

        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(FIFO_priority[i]>=temp)
            {
                temp = FIFO_priority[i];
                j = i;
            }
        }

        current_line = j;
    }
}

void FIFOUnhitUnspace_2()
{
	if(t_assoc == full_associative)
    {
        temp_2 = FIFO_priority_2[0];

        for(i=0; i<i_num_line_2; i++)
        {
            if(FIFO_priority_2[i]>=temp_2)
            {
                temp_2 = FIFO_priority_2[i];
                j = i;
            }
        }

        current_line_2 = j;
    }

	if(t_assoc == set_associative)
    {
        temp_2 = FIFO_priority_2[current_set_2*i_cache_set_2];

        for(i=(current_set_2*i_cache_set_2); i<((current_set_2+1)*i_cache_set_2); i++)
        {
            if(FIFO_priority_2[i]>=temp_2)
            {
                temp_2 = FIFO_priority_2[i];
                j = i;
            }
        }

        current_line_2 = j;
    }
}