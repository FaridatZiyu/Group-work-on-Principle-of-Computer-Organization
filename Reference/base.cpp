/** \brief definition of almost all globle variables.
 *
 * \param
 * \param
 * \return
 *
 */

#include "base.h"

/******************************************/
unsigned int long total_cycle = 0;
unsigned int long cost_of_cache_1 = 0, cycle_of_cache_1 = 0;
unsigned int long cost_of_cache_2 = 0, cycle_of_cache_2 = 0; 
unsigned int long cost_of_memory = 0, cycle_of_memory = 0;
unsigned int long i_cache_size = 0, i_cache_size_2 = 0; //cache size
unsigned int long i_cache_line_size = 0, i_cache_line_size_2 = 0; //cacheline size
unsigned int long i_cache_set = 0, i_cache_set_2 = 0; //cache set
unsigned int long i_num_line = 0, i_num_line_2 = 0; //How many lines of the cache
unsigned int long i_num_set = 0, i_num_set_2 = 0; //How many sets of the cache

ASSOC t_assoc = direct_mapped; //associativity method,default direct_mapped
REPLACE t_replace = none; //replacement policy,default Random
WRITE t_write = write_back; //write policy,default write_back
/******************************************/

/******************************************/
short unsigned int bit_block = 0, bit_block_2 = 0; //How many bits of the block.
short unsigned int bit_line = 0, bit_line_2 = 0; //How many bits of the line.
short unsigned int bit_tag = 0, bit_tag_2 = 0; //How many bits of the tag.
short unsigned int bit_set = 0, bit_set_2 = 0; //How many bits of the set.
/******************************************/

/******************************************/
unsigned long int i_num_access = 0, i_num_access_2 = 0; //Number of cache access
unsigned long int i_num_load = 0, i_num_load_2 = 0; //Number of cache load
unsigned long int i_num_store = 0, i_num_store_2 = 0; //Number of cache store
unsigned long int i_num_space = 0, i_num_space_2 = 0; //Number of space line

unsigned long int i_num_hit = 0, i_num_hit_2 = 0; //Number of cache hit
unsigned long int i_num_load_hit = 0, i_num_load_hit_2 = 0; //Number of load hit
unsigned long int i_num_store_hit = 0, i_num_store_hit_2 = 0; //Number of store hit

float f_ave_rate = 0.0, f_ave_rate_2 = 0.0; //Average cache hit rate
float f_load_rate = 0.0, f_load_rate_2 = 0.0; //Cache hit rate for loads
float f_store_rate = 0.0, f_store_rate_2 = 0.0; //Cache hit rate for stores
/******************************************/

std::bitset<32> cache_item[MAX_CACHE_LINE]; // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data
std::bitset<32> cache_item_2[MAX_CACHE_LINE];
unsigned long int LRU_priority[MAX_CACHE_LINE]; // For LRU policy's priority
unsigned long int LRU_priority_2[MAX_CACHE_LINE];
unsigned long int FIFO_priority[MAX_CACHE_LINE]; // For FIFO policy's priority
unsigned long int FIFO_priority_2[MAX_CACHE_LINE];
unsigned long int LFU_priority[MAX_CACHE_LINE]; // For LFU policy's priority
unsigned long int LFU_priority_2[MAX_CACHE_LINE];
unsigned long int current_line = 0, current_line_2 = 0; // The line num which is processing
unsigned long int current_set = 0, current_set_2 = 0; // The set num which is processing
unsigned long int i=0,j=0; //For loop
unsigned long int temp = 0, temp_2 = 0; //A temp varibale


/*************************************************
// functions.cpp
// 1.Defination of almost all functions.
*************************************************/

using namespace std;

bool GetHitNum(char *address)
{
    bool is_store = false;
    bool is_load = false;
    bool is_space = false;
    bool hit = false;
	bool hit_2 = false;

    switch(address[0])     //因为只有load-store才涉及访存，其他指令都在流水线里，跟我们的cache无关
    {
    case 's':
        is_store = true;
        break;

    case 'l':
        is_load = true;
        break;

    //case ' ':break; //Waring if a line has nothing,the first of it is a '\0' nor a ' '
    case '\0':
        is_space = true;
        break; //In case of space lines

    default:
        cout << "The address[0] is:" <<address[0] << endl;
        cout << "ERROR IN JUDGE!" << endl;
        return false;
    }

    temp = strtoul(address+2,NULL,16); //按16进制把字符串转换成unsigned long
	bitset<32> flags((_ULonglong)temp); // flags if the binary of address, 把temp地址转化为一个32位的bitset对象叫flags，前面不足的填零
#ifndef NDEBUG
    cout << flags << endl;
#endif // NDEBUG
    hit = IsHit(flags);   //判断一级cache有没有命中
	hit_2 = IsHit_2(flags);   //判断二级cache有没有命中

    if(hit && is_load) // 命中，读操作
    {
        i_num_access++;
        i_num_load++;
		i_num_hit++;
        i_num_load_hit++;
#ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Hit" << endl;
        cout << "Read from Cache!" << endl;
#endif // NDEBUG

        if(t_replace == LRU)
        {
            LruHitProcess();
        }
		else if(t_replace == FIFO)
		{
			FIFOHitProcess();
		}
		else if(t_replace == LFU)
		{
			LfuHitProcess();
		}
    }
    else if(hit && is_store) // 命中，写操作
    {
        i_num_access++;
        i_num_store++;
        i_num_store_hit++;
        i_num_hit++;
#ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Hit" << endl;
        cout << "Write to Cache" << endl;
#endif // NDEBUG
        cache_item[current_line][29] = true; //设置dirty为true

        if(t_replace == LRU)
        {
            LruHitProcess();
        }
		else if(t_replace == FIFO)
		{
			FIFOHitProcess();
		}
		else if(t_replace == LFU)
		{
			LfuHitProcess();
		}
    }

    else if((!hit) && is_load && hit_2) // 一级没命中，二级命中了，读操作
    {
        i_num_access++;i_num_access_2++;
        i_num_load++;i_num_load_2++;
		i_num_hit_2++;
        i_num_load_hit_2++;
#ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Not Hit" << endl;
#endif // NDEBUG
        GetRead(flags);
#ifndef NDEBUG
        cout << "Read from Cache!" << endl;
#endif // NDEBUG

        if(t_replace == LRU)
        {
            LruUnhitSpace();
			LruHitProcess_2();
        }
		else if(t_replace ==FIFO)
		{
			FIFOUnhitSpace();
			FIFOHitProcess_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitSpace();
			LfuHitProcess_2();
		}
    }
	else if((!hit) && is_load && (!hit_2)) // 全部没命中，读操作
    {
        i_num_access++;i_num_access_2++;
        i_num_load++;i_num_load_2++;
#ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Not Hit" << endl;
#endif // NDEBUG
        GetRead(flags);
		GetRead_2(flags);
#ifndef NDEBUG
        cout << "Read from Cache!" << endl;
#endif // NDEBUG

        if(t_replace == LRU)
        {
            LruUnhitSpace();
			LruUnhitSpace_2();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitSpace();
			FIFOUnhitSpace_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitSpace();
			LfuUnhitSpace_2();
		}
    }

    else if((!hit) && is_store && hit_2) // 一级没命中，二级命中了，写操作
    {
        i_num_access++;i_num_access_2++;
        i_num_store++;i_num_store_2++;
		i_num_hit_2++;
        i_num_store_hit_2++;
#ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Not Hit" << endl;
#endif // NDEBUG
        GetRead(flags);
#ifndef NDEBUG
        cout << "Write to Cache" << endl;
#endif // NDEBUG
        cache_item[current_line][29] = true; //设置dirty为true

        if(t_replace == LRU)
        {
            LruUnhitSpace();
			LruHitProcess_2();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitSpace();
			FIFOHitProcess_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitSpace();
			LfuHitProcess_2();
		}
    }
	else if((!hit) && is_store && !(hit_2)) // 全部没命中，写操作
    {
        i_num_access++;i_num_access_2++;
        i_num_store++;i_num_store_2++;
#ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Not Hit" << endl;
#endif // NDEBUG
        GetRead(flags);
		GetRead_2(flags);
#ifndef NDEBUG
        cout << "Write to Cache" << endl;
#endif // NDEBUG
        cache_item[current_line][29] = true; //设置dirty为true

        if(t_replace == LRU)
        {
            LruUnhitSpace();
			LruUnhitSpace_2();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitSpace();
			FIFOUnhitSpace_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitSpace();
			LfuUnhitSpace_2();
		}
    }

    else if(is_space)
    {
        i_num_space++;
		i_num_space_2++;
    }
    else
    {
        cerr << "Something ERROR" << endl;
        return false;
    }

    if(i_num_space != 0 || i_num_space_2 !=0)
    {
#ifndef NDEBUG
        cout << "There have " << i_num_space << "and" << i_num_space_2 << " space lines" << endl;
#endif // NDEBUG
    }

    return true;
}

bool IsHit(bitset<32> flags)
{
    bool ret = false;

    if(t_assoc == direct_mapped)   
    {
        bitset<32> flags_line; // a temp variable

        for(j=0,i=(bit_block); i<(bit_block+bit_line); j++,i++) //判断在cache多少行
        {
            flags_line[j] = flags[i];
        }

        current_line = flags_line.to_ulong();
        assert(cache_item[current_line][31] == true);

        if(cache_item[current_line][30]==true) //判断hit位是否为真
        {
            ret = true;

            for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //判断标记是否相同,i:address,j:cache
            {
                if(flags[i] != cache_item[current_line][j])
                {
                    ret = false;
                    break;
                }
            }
        }
    }
    else if(t_assoc == full_associative)
    {
        for(temp=0; temp<i_num_line; temp++)
        {
            if(cache_item[temp][30]==true) //判断hit位是否为真
            {
                ret = true;

                for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //判断标记是否相同,i:address,j:cache
                {
                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }

            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }
    }
    else if(t_assoc == set_associative)
    {
        bitset<32> flags_set;

        for(j=0,i=(bit_block); i<(bit_block+bit_set); j++,i++) //判断在cache多少组
        {
            flags_set[j] = flags[i];
        }

        current_set = flags_set.to_ulong();

        for(temp=(current_set*i_cache_set); temp<((current_set+1)*i_cache_set); temp++)
        {
            if(cache_item[temp][30]==true) //判断hit位是否为真
            {
                ret = true;

                for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //判断标记是否相同,i:address,j:cache
                {
                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }

            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }
    }

    return ret;
}

bool IsHit_2(bitset<32> flags)
{
    bool ret = false;

    if(t_assoc == direct_mapped)   
    {
        bitset<32> flags_line; // a temp_2 variable

        for(j=0,i=(bit_block_2); i<(bit_block_2+bit_line_2); j++,i++) //判断在cache多少行
        {
            flags_line[j] = flags[i];
        }

        current_line_2 = flags_line.to_ulong();
        assert(cache_item_2[current_line_2][31] == true);

        if(cache_item_2[current_line_2][30]==true) //判断hit位是否为真
        {
            ret = true;

            for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //判断标记是否相同,i:address,j:cache
            {
                if(flags[i] != cache_item_2[current_line_2][j])
                {
                    ret = false;
                    break;
                }
            }
        }
    }
    else if(t_assoc == full_associative)
    {
        for(temp_2=0; temp_2<i_num_line_2; temp_2++)
        {
            if(cache_item_2[temp_2][30]==true) //判断hit位是否为真
            {
                ret = true;

                for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //判断标记是否相同,i:address,j:cache
                {
                    if(flags[i] != cache_item_2[temp_2][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }

            if(ret == true)
            {
                current_line_2 = temp_2;
                break;
            }
        }
    }
    else if(t_assoc == set_associative)
    {
        bitset<32> flags_set;

        for(j=0,i=(bit_block_2); i<(bit_block_2+bit_set_2); j++,i++) //判断在cache多少组
        {
            flags_set[j] = flags[i];
        }

        current_set_2 = flags_set.to_ulong();

        for(temp_2=(current_set_2*i_cache_set_2); temp_2<((current_set_2+1)*i_cache_set_2); temp_2++)
        {
            if(cache_item_2[temp_2][30]==true) //判断hit位是否为真
            {
                ret = true;

                for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //判断标记是否相同,i:address,j:cache
                {
                    if(flags[i] != cache_item_2[temp_2][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }

            if(ret == true)
            {
                current_line_2 = temp_2;
                break;
            }
        }
    }

    return ret;
}

void GetRead(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
        if(cache_item[current_line][30] == false) //hit is false
        {
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //设置标记
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }

            cache_item[current_line][30] = true; //设置hit位为true
        }
        else
        {
            GetReplace(flags);
        }
    }
    else if(t_assoc == full_associative)
    {
        bool space = false;

        for(temp=0; temp<i_num_line; temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line = temp; // 此处，temp不需减1，因为一旦发现空行，上面for循环会break，此时temp尚未++
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //设置标记
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }

            cache_item[current_line][30] = true; //设置hit位为true.

            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }
			else if(t_replace == FIFO)
			{
				FIFOUnhitSpace();
			}
			else if(t_replace == LFU)
			{
				LfuUnhitSpace();
			}
        }
        else
        {
            GetReplace(flags);
        }
    }
    else if(t_assoc == set_associative)
    {
        bool space = false;

        for(temp=(current_set*i_cache_set); temp<((current_set+1)*i_cache_set); temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line = temp; // 此处，temp不需减1，因为一旦发现空行，上面for循环会break，此时temp尚未++
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //设置标记
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }

            cache_item[current_line][30] = true; //设置hit位为true.

            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }
			else if(t_replace == FIFO)
			{
				FIFOUnhitSpace();
			}
			else if(t_replace == LFU)
			{
				LfuUnhitSpace();
			}
        }
        else
        {
            GetReplace(flags);
        }
    }
}

void GetRead_2(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
        if(cache_item_2[current_line_2][30] == false) //hit is false
        {
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //设置标记
            {
                cache_item_2[current_line_2][j] = flags[i];
                assert(j>0);
            }

            cache_item_2[current_line_2][30] = true; //设置hit位为true
        }
        else
        {
            GetReplace_2(flags);
        }
    }
    else if(t_assoc == full_associative)
    {
        bool space = false;

        for(temp_2=0; temp_2<i_num_line_2; temp_2++)
        {
            if(cache_item_2[temp_2][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line_2 = temp_2; // 此处，temp_2不需减1，因为一旦发现空行，上面for循环会break，此时temp_2尚未++
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //设置标记
            {
                cache_item_2[current_line_2][j] = flags[i];
                assert(j>0);
            }

            cache_item_2[current_line_2][30] = true; //设置hit位为true.

            if(t_replace == LRU)
            {
                LruUnhitSpace_2();
            }
			else if(t_replace == FIFO)
			{
				FIFOUnhitSpace_2();
			}
			else if(t_replace == LFU)
			{
				LfuUnhitSpace_2();
			}
        }
        else
        {
            GetReplace_2(flags);
        }
    }
    else if(t_assoc == set_associative)
    {
        bool space = false;

        for(temp_2=(current_set_2*i_cache_set_2); temp_2<((current_set_2+1)*i_cache_set_2); temp_2++)
        {
            if(cache_item_2[temp_2][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line_2 = temp_2; // 此处，temp_2不需减1，因为一旦发现空行，上面for循环会break，此时temp_2尚未++
#ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
#endif // NDEBUG

            for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //设置标记
            {
                cache_item_2[current_line_2][j] = flags[i];
                assert(j>0);
            }

            cache_item_2[current_line_2][30] = true; //设置hit位为true.

            if(t_replace == LRU)
            {
                LruUnhitSpace_2();
            }
			else if(t_replace == FIFO)
			{
				FIFOUnhitSpace_2();
			}
			else if(t_replace == LFU)
			{
				LfuUnhitSpace_2();
			}
        }
        else
        {
            GetReplace_2(flags);
        }
    }
}

void GetReplace(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
    }
    else if(t_assoc == full_associative)
    {
        if(t_replace == Random)
        {
            current_line = rand()/(RAND_MAX/i_num_line+1); // a random line in(0,i_num_line-1)
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitUnspace();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitUnspace();
		}
    }
    else if(t_assoc == set_associative) // 从本组中任选一行，进行替换
    {
        if(t_replace == Random)
        {
            temp = rand()/(RAND_MAX/i_cache_set+1); // a random line in(0,i_cache_set-1)
            current_line = current_set*i_cache_set+temp; // a random line in current_set
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitUnspace();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitUnspace();
		}
    }

    if(cache_item[current_line][29] == true) //dirty-bit==1，说明这里已被修改但还未写入内存，在替换掉这里的块之前赶紧写存
    {
        GetWrite(); //写入内存
    }

#ifndef NDEBUG
    cout << "Read from Main Memory to Cache: " << endl;
#endif // NDEBUG

    for(i=31,j=28; i>(31ul-bit_tag); i--,j--) //设置标记
    {
        cache_item[current_line][j] = flags[i];
        assert(j>0);
    }

    cache_item[current_line][30] = true; //设置hit位为true
}

void GetReplace_2(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
    }
    else if(t_assoc == full_associative)
    {
        if(t_replace == Random)
        {
            current_line_2 = rand()/(RAND_MAX/i_num_line_2+1); // a random line in(0,i_num_line_2-1)
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace_2();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitUnspace_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitUnspace_2();
		}
    }
    else if(t_assoc == set_associative) // 从本组中任选一行，进行替换
    {
        if(t_replace == Random)
        {
            temp_2 = rand()/(RAND_MAX/i_cache_set_2+1); // a random line in(0,i_cache_set_2-1)
            current_line_2 = current_set_2*i_cache_set_2+temp_2; // a random line in current_set_2
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace_2();
        }
		else if(t_replace == FIFO)
		{
			FIFOUnhitUnspace_2();
		}
		else if(t_replace == LFU)
		{
			LfuUnhitUnspace_2();
		}
    }

    if(cache_item_2[current_line_2][29] == true) //dirty-bit==1，说明这里已被修改但还未写入内存，在替换掉这里的块之前赶紧写存
    {
        GetWrite_2(); //写入内存
    }

#ifndef NDEBUG
    cout << "Read from Main Memory to Cache: " << endl;
#endif // NDEBUG

    for(i=31,j=28; i>(31ul-bit_tag_2); i--,j--) //设置标记
    {
        cache_item_2[current_line_2][j] = flags[i];
        assert(j>0);
    }

    cache_item_2[current_line_2][30] = true; //设置hit位为true
}

void GetWrite() //写入内存
{
#ifndef NDEBUG
    cout << "Writing to the Main Memory!" <<endl;
#endif
    cache_item[current_line][29] = false; //设置dirty为false
    cache_item[current_line][30] = false; //设置hit为false
}

void GetWrite_2() //写入内存
{
#ifndef NDEBUG
    cout << "Writing to the Main Memory!" <<endl;
#endif
    cache_item_2[current_line_2][29] = false; //设置dirty为false
    cache_item_2[current_line_2][30] = false; //设置hit为false
}

void GetHitRate()
{
    assert(i_num_access != 0 && i_num_access_2 != 0);
    assert(i_num_load != 0 && i_num_load_2 != 0);
    assert(i_num_store != 0 && i_num_store_2 != 0);
    f_ave_rate = ((double)i_num_hit)/i_num_access; //Average cache hit rate
	f_ave_rate_2 = ((double)i_num_hit_2)/i_num_access_2;
    f_load_rate = ((double)i_num_load_hit)/i_num_load; //Cache hit rate for loads
	f_load_rate_2 = ((double)i_num_load_hit_2)/i_num_load_2; 
    f_store_rate = ((double)i_num_store_hit)/i_num_store; //Cache hit rate for stores
	f_store_rate_2 = ((double)i_num_store_hit_2)/i_num_store_2;
}

void GetCost()
{
	cycle_of_cache_1 = i_num_access * cost_of_cache_1;
	cycle_of_cache_2 = i_num_access_2 * cost_of_cache_2;
	cycle_of_memory = (i_num_access_2 - i_num_hit_2) * cost_of_memory;
	total_cycle = cycle_of_cache_1 + cycle_of_cache_2 + cycle_of_memory;
}