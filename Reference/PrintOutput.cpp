#include "base.h"

using namespace std;

void PrintOutput(void)
{
    cout << endl;
    cout << "Cache Size:" << i_cache_size << "KB" << endl;
    cout << "Cacheline Size:" << i_cache_line_size << "B" << endl;
	cout << "Cache_2 Size:" << i_cache_size_2 << "KB" << endl;
    cout << "Cacheline_2 Size:" << i_cache_line_size_2 << "B" << endl;

    switch(t_assoc)
    {
    case 1:
        cout << "Way of Associativity:direct_mapped" << endl;
        break;

    case 2:
        cout << "Way of Associativity:set_associative" << endl;
        break;

    case 3:
        cout << "Way of Associativity:full_associative" << endl;
        break;

    default:
        cerr << "ERROR ASSOCIATIVITY";
        break;
    }

    switch(t_replace)
    {
    case 0:
        cout << "Way of Replacement:NONE" << endl;
        break;

    case 1:
        cout << "Way of Replacement:FIFO" << endl;
        break;

    case 2:
        cout << "Way of Replacement:LRU" << endl;
        break;

    case 3:
        cout << "Way of Replacement:LFU" << endl;
        break;

    case 4:
        cout << "Way of Replacement:Random" << endl;
        break;

    default:
        cerr << "ERROR REPLACEMENT";
        break;
    }

    switch(t_write)
    {
    case 1:
        cout << "Way of Write:write_through" << endl;
        break;

    case 2:
        cout << "Way of Write:write_back" << endl;
        break;

    default:
        cerr << "ERROR WRITE";
        break;
    }

    cout << endl;
    cout << "Number of cache_1 access:" << i_num_access << endl;
    cout << "Number of cache_1 load:" << i_num_load << endl;
    cout << "Number of cache_1 store:" << i_num_store << endl;
    cout << endl;
    cout << "Average cache_1 hit rate:" << f_ave_rate*100 << "%" << endl;
    cout << "Cache_1 hit rate for loads:" << f_load_rate*100 << "%" << endl;
    cout << "Cache_1 hit rate for stores:" << f_store_rate*100 << "%" << endl;
    cout << endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << endl;
    cout << "Number of cache_2 access:" << i_num_access_2 << endl;
    cout << "Number of cache_2 load:" << i_num_load_2 << endl;
    cout << "Number of cache_2 store:" << i_num_store_2 << endl;
    cout << endl;
    cout << "Average cache_2 hit rate:" << f_ave_rate_2*100 << "%" << endl;
    cout << "cache_2 hit rate for loads:" << f_load_rate_2*100 << "%" << endl;
    cout << "cache_2 hit rate for stores:" << f_store_rate_2*100 << "%" << endl;
    cout << endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << endl;
    cout << "Cycle of cache_1:" << cycle_of_cache_1 << endl;
    cout << "Cycle of cache_2:" << cycle_of_cache_2 << endl;
    cout << "Cycle of memory:" << cycle_of_memory << endl;
	cout<<"Cycle of total:" << total_cycle <<endl;
    cout << endl;
}

