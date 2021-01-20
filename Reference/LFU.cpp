#include "base.h"

using namespace std;

void LfuHitProcess()
{
	if(t_assoc == full_associative || t_assoc == set_associative)
		 LFU_priority[current_line]++;
}

void LfuHitProcess_2()
{
	if(t_assoc == full_associative || t_assoc == set_associative)
		 LFU_priority_2[current_line_2]++;
}

void LfuUnhitSpace()
{
	if(t_assoc == full_associative || t_assoc == set_associative)
		LFU_priority[current_line]++;
}

void LfuUnhitSpace_2()
{
	if(t_assoc == full_associative || t_assoc == set_associative)
		LFU_priority_2[current_line_2]++;
}

void LfuUnhitUnspace()
{
	if(t_assoc == full_associative)
    {
        temp = LFU_priority[0];

        for(i=0; i<i_num_line; i++)
        {
            if(LFU_priority[i]<=temp)
            {
                temp = LFU_priority[i];
                j = i;
            }
        }

        current_line = j;
    }

    if(t_assoc == set_associative)
    {
        temp = LFU_priority[current_set*i_cache_set];

        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(LFU_priority[i]<=temp)
            {
                temp = LFU_priority[i];
                j = i;
            }
        }

        current_line = j;
    }
}

void LfuUnhitUnspace_2()
{
	if(t_assoc == full_associative)
    {
        temp_2 = LFU_priority_2[0];

        for(i=0; i<i_num_line_2; i++)
        {
            if(LFU_priority_2[i]<=temp_2)
            {
                temp_2 = LFU_priority_2[i];
                j = i;
            }
        }

        current_line_2 = j;
    }

    if(t_assoc == set_associative)
    {
        temp_2 = LFU_priority_2[current_set_2*i_cache_set_2];

        for(i=(current_set_2*i_cache_set_2); i<((current_set_2+1)*i_cache_set_2); i++)
        {
            if(LFU_priority_2[i]<=temp_2)
            {
                temp_2 = LFU_priority_2[i];
                j = i;
            }
        }

        current_line_2 = j;
    }
}