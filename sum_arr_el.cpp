#include "sum_arr_el.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>

SumElArr::SumElArr(int _size, int _number_threads): 
    size(_size), number_threads(_number_threads) {
        const int min_value = 0;
        const int max_value = 10;
        srand(std::time(0));
        for (int i = 0; i < size; i++) {
            values.push_back(min_value + rand() % (max_value - min_value + 1));
        }
}

SumElArr::~SumElArr() {};

void SumElArr::sum_one_part(int l_index, int r_index, int index)
{
    int s = 0;
    while (l_index <= r_index)
    {
        s += values[l_index++];
    }
    sum_arr_el += s;
    //std::cout << "Thread id = " << std::this_thread::get_id() << "  index = " << index << " sum = " << s << std::endl;
}

int SumElArr::sum_threads_main() {
    int s = 0;
    for (int i = 0; i < values.size(); i++)
    {
        s += values[i];
    }
    return s;
}

int SumElArr::sum_threads() {
    std::vector<std::thread> threads;
    int l_index = 0;
    int r_index = 0;
    int elements_count = size/number_threads;
    sum_arr_el = 0;

    for (int i = 0; i < number_threads; i++)
    {
        if (i == number_threads - 1)
            r_index = values.size();    //if we have left elements, we consider them
        else
            r_index += elements_count;

        //create a thread
        std::thread t(&SumElArr::sum_one_part, this, l_index, r_index - 1, i);
        //we cannot copy a thread object so we move it
        threads.push_back(std::move(t));
        l_index += elements_count;
    }

    for (auto& t: threads)
    {
        if (t.joinable())
            t.join();
    }

    return sum_arr_el;
}