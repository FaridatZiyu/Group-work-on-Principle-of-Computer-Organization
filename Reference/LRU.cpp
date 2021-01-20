#include "base.h"

using namespace std;

void LruHitProcess() // if the replacement policy is LRU,and hit
{
    if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line; i++)
        {
            if(LRU_priority[i]<LRU_priority[current_line] && cache_item[current_line][30]==true)
            {
                LRU_priority[i]++; // 如果该行比正在访问的行计数器值小，并且该行中hit为true
            }
        }

        LRU_priority[current_line] = 0;
    }
    else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(LRU_priority[i]<LRU_priority[current_line] && cache_item[current_line][30]==true)
            {
                LRU_priority[i]++; // 如果该行比正在访问的行计数器值小，并且该行中hit为true
            }
        }

        LRU_priority[current_line] = 0;
    }
}

void LruHitProcess_2() // if the replacement policy is LRU,and hit
{
    if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line_2; i++)
        {
            if(LRU_priority_2[i]<LRU_priority_2[current_line] && cache_item_2[current_line][30]==true)
            {
                LRU_priority_2[i]++; // 如果该行比正在访问的行计数器值小，并且该行中hit为true
            }
        }

        LRU_priority_2[current_line] = 0;
    }
    else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set_2); i<((current_set+1)*i_cache_set_2); i++)
        {
            if(LRU_priority_2[i]<LRU_priority_2[current_line] && cache_item_2[current_line][30]==true)
            {
                LRU_priority_2[i]++; // 如果该行比正在访问的行计数器值小，并且该行中hit为true
            }
        }

        LRU_priority_2[current_line] = 0;
    }
}

void LruUnhitSpace() // if the replacement policy is LRU,and not hit,but there has a spaceline
{
    if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line; i++)
        {
            if(cache_item[current_line][30]==true)
            {
                LRU_priority[i]++; // 如果该行该行中hit为true
            }
        }

        LRU_priority[current_line] = 0;
    }
    else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(cache_item[current_line][30]==true)
            {
                LRU_priority[i]++; // 如果该行该行中hit为true
            }
        }

        LRU_priority[current_line] = 0;
    }
}

void LruUnhitSpace_2() // if the replacement policy is LRU,and not hit,but there has a spaceline
{
    if(t_assoc == full_associative)
    {
        for(i=0; i<i_num_line_2; i++)
        {
            if(cache_item_2[current_line][30]==true)
            {
                LRU_priority_2[i]++; // 如果该行该行中hit为true
            }
        }

        LRU_priority_2[current_line] = 0;
    }
    else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set_2); i<((current_set+1)*i_cache_set_2); i++)
        {
            if(cache_item_2[current_line][30]==true)
            {
                LRU_priority_2[i]++; // 如果该行该行中hit为true
            }
        }

        LRU_priority_2[current_line] = 0;
    }
}

void LruUnhitUnspace()
{
    if(t_assoc == full_associative)
    {
        temp = LRU_priority[0];

        for(i=0; i<i_num_line; i++)
        {
            if(LRU_priority[i]>=temp)
            {
                temp = LRU_priority[i];
                j = i;
            }
        }

        current_line = j;
    }

    if(t_assoc == set_associative)
    {
        temp = LRU_priority[current_set*i_cache_set];

        for(i=(current_set*i_cache_set); i<((current_set+1)*i_cache_set); i++)
        {
            if(LRU_priority[i]>=temp)
            {
                temp = LRU_priority[i];
                j = i;
            }
        }

        current_line = j;
    }
}

void LruUnhitUnspace_2()
{
    if(t_assoc == full_associative)
    {
        temp_2 = LRU_priority_2[0];

        for(i=0; i<i_num_line_2; i++)
        {
            if(LRU_priority_2[i]>=temp_2)
            {
                temp_2 = LRU_priority_2[i];
                j = i;
            }
        }

        current_line = j;
    }

    if(t_assoc == set_associative)
    {
        temp_2 = LRU_priority_2[current_set*i_cache_set_2];

        for(i=(current_set*i_cache_set_2); i<((current_set+1)*i_cache_set_2); i++)
        {
            if(LRU_priority_2[i]>=temp_2)
            {
                temp_2 = LRU_priority_2[i];
                j = i;
            }
        }

        current_line = j;
    }
}

