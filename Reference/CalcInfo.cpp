#include "base.h"

using namespace std;


void CalcInfo()
{
    assert(i_cache_line_size != 0 && i_cache_line_size_2 != 0);
    i_num_line = (i_cache_size<<10)/i_cache_line_size;
	 i_num_line_2 = (i_cache_size_2<<10)/i_cache_line_size_2;
    temp = i_cache_line_size; //计算块内地址位数(块内偏移)
	temp_2 = i_cache_line_size_2;

    while(temp)
    {
        temp >>= 1;
        bit_block++;
    }
	
    while(temp_2)
    {
        temp_2 >>= 1;
        bit_block_2++;
    }

    bit_block--; //warning
	bit_block_2--;

    if(t_assoc == direct_mapped)
    {
        bit_set = 0; // for direct_mapped,the bit_set is 0
		bit_set_2 = 0;
        temp = i_num_line;
		temp_2 = i_num_line_2;

        while(temp)
        {
            temp >>= 1;
            bit_line++;
        }

		 while(temp_2)
        {
            temp_2 >>= 1;
            bit_line_2++;
        }

        bit_line--; //warning
		bit_line_2--;
    }
    else if(t_assoc == full_associative)
    {
        bit_line = 0; // for full_associative,the bit_line is 0，全相联无索引位数
		bit_line_2 = 0;
        bit_set = 0; // for full_associative,the bit_set is 0,   全相联没有组数
		bit_set_2 = 0;
    }
    else if(t_assoc == set_associative)
    {
        bit_line = 0; // for set_associative,the bit_line is 0,  组相联也不需要索引位数
		bit_line_2 = 0;
        assert(i_cache_set != 0 && i_cache_set_2 != 0);
        assert(i_num_line > i_cache_set && i_num_cache_2 > i_cache_set_2);
        i_num_set = i_num_line/i_cache_set;
		i_num_set_2 = i_num_line_2/i_cache_set_2;
        temp = i_num_set;
		temp_2 = i_num_set_2;

        while(temp)
        {
            temp >>= 1;
            bit_set++;
        }

		while(temp_2)
        {
            temp_2 >>= 1;
            bit_set_2++;
        }

        bit_set--;
		bit_set_2--;
    }

    bit_tag = 32ul - bit_block - bit_line - bit_set;      //标记需要多少位
	bit_tag_2 = 32ul - bit_block_2 - bit_line_2 - bit_set_2;
    assert(bit_tag <= 29 && bit_tag_2 <= 29); //32-valid-hit-dirty
    cout << "i_cache_line_size: " << i_cache_line_size << "B" << endl; // 显示块大小
    cout << "i_cache_size: " << i_cache_size << "KB" << endl; // 显示cache数据区总容量

    if(t_assoc == set_associative) // 如果为组相联，显示是几路组相联
    {
        cout << "i_cache_set: " << i_cache_set << " lines each set" << endl;
    }

    cout << "i_num_line: " << i_num_line << endl; // 显示共有多少行

    if(t_assoc == set_associative) // 如果为组相联，显示共有几组
    {
        cout << "i_num_set: " << i_num_set << endl;
    }

    cout << "bit_block: " << bit_block << endl; // 显示块内地址所需位数

    if(t_assoc == direct_mapped) // 如果为直接映射，显示行号所需位数
    {
        cout << "bit_line: " << bit_line << endl;
    }

    if(t_assoc == set_associative) // 如果为组相联，显示组号所需位数
    {
        cout << "bit_set: " << bit_set << endl;
    }

    cout << "bit_tag: " << bit_tag << endl; // 显示标志位所需位数

	
	cout << "i_cache_line_size_2: " << i_cache_line_size_2 << "B" << endl;
	cout << "i_cache_size_2: " << i_cache_size_2 << "KB" << endl;

    if(t_assoc == set_associative) 
    {
		cout << "i_cache_set_2: " << i_cache_set_2 << " lines each set" << endl;
    }
	cout << "i_num_line_2: " << i_num_line_2 << endl;

    if(t_assoc == set_associative) 
    {
		cout << "i_num_set_2: " << i_num_set_2 << endl;
    }
	cout << "bit_block_2: " << bit_block_2 << endl;

    if(t_assoc == direct_mapped) 
    {
		cout << "bit_line_2: " << bit_line_2 << endl;
    }

    if(t_assoc == set_associative) 
    {
		cout << "bit_set_2: " << bit_set_2 << endl;
    }
	cout << "bit_tag_2: " << bit_tag_2 << endl;
}
