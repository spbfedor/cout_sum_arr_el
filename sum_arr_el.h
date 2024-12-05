#pragma once

#include <vector>

class SumElArr{
    private:
        int size;
        int number_threads;
        std::vector<int>values;
        int sum_arr_el;
        void sum_one_part(int left_insex, int right_index, int index);
    public:
        SumElArr(int _size, int _number_threads);
        ~SumElArr();
        int sum_threads();
        int sum_threads_main();
};