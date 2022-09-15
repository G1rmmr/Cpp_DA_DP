#include <iostream>
#include <vector>
#include <chrono>

template <typename T>
auto Partition(typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator end)
{
    auto pivot_val = *begin;
    auto left_iter = begin + 1;
    auto right_iter = end;

    while(true)
    {
        while(*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
            left_iter++;

        while(*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
            right_iter--;
        
        if(left_iter == right_iter) break;
        else std::iter_swap(left_iter, right_iter);
    }

    if(pivot_val > *right_iter) std::iter_swap(begin, right_iter);
    return right_iter;
}

template <typename T>
void QuickSort(typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator last)
{
    if(std::distance(begin, last) >= 1)
    {
        auto partition_iter = Partition<T>(begin, last);
        QuickSort<T>(begin, partition_iter - 1);
        QuickSort<T>(partition_iter, last);
    }
}

template <typename T>
void PartialSort(typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator last, int k)
{
    if(std::distance(begin, last) >= 1)
    {
        auto partition_iter = Partition<T>(begin, last);

        if(partition_iter - begin - 1 < k) PartialSort<T>(partition_iter, last, k);
        else PartialSort<T>(begin, partition_iter - 1, k);
    }
}

template <typename T>
void PrintVector(std::vector<T> arr)
{
    for(auto e : arr) std::cout << e << ' ';
    std::cout << std::endl;
}

void RunQuickSortTest()
{
    std::vector<int> s {60, 17, 15, 62, 82, 58, 73, 1, 21, 48, 2, 43
                    , 86, 30, 18, 29, 44, 81, 56, 41, 43, 17, 37, 72
                    , 11, 48, 100, 53, 14, 51, 45, 10, 70, 12, 51, 4
                    , 36, 99, 32, 41, 41, 84, 73, 33, 90, 67, 22, 58
                    , 38, 30, 85, 18, 64, 50, 36, 59, 73, 34, 68, 93
                    , 62, 18, 49, 27, 5, 9, 21, 77, 10, 60, 64, 1, 47
                    , 57, 81, 55, 7, 66, 17, 55, 29, 14, 85, 9, 79
                    , 85, 73, 16, 19, 96, 53, 22, 83, 80, 4, 94};

    std::cout << "<Unsorted input vector>\n" << std::endl;

    PrintVector<int>(s);
    std::cout << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    QuickSort<int>(s.begin(), s.end() - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Quick sort operating time: " << diff.count() << std::endl;
    std::cout << "<Now, all vectors are sorted>\n" << std::endl;

    PrintVector<int>(s);
    std::cout << std::endl;
}

void RunPartialSortTest()
{
    const int k = 10;

    std::vector<int> s {60, 17, 15, 62, 82, 58, 73, 1, 21, 48, 2, 43
                    , 86, 30, 18, 29, 44, 81, 56, 41, 43, 17, 37, 72
                    , 11, 48, 100, 53, 14, 51, 45, 10, 70, 12, 51, 4
                    , 36, 99, 32, 41, 41, 84, 73, 33, 90, 67, 22, 58
                    , 38, 30, 85, 18, 64, 50, 36, 59, 73, 34, 68, 93
                    , 62, 18, 49, 27, 5, 9, 21, 77, 10, 60, 64, 1, 47
                    , 57, 81, 55, 7, 66, 17, 55, 29, 14, 85, 9, 79
                    , 85, 73, 16, 19, 96, 53, 22, 83, 80, 4, 94};

    std::cout << "<Unsorted input vector>\n" << std::endl;

    PrintVector<int>(s);
    std::cout << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    PartialSort<int>(s.begin(), s.end() - 1, k);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Partial sort operating time: " << diff.count() << std::endl;
    std::cout << "<Now, 10 datas in vector are sorted>\n" << std::endl;

    PrintVector<int>(s);
    std::cout << std::endl;
}

int main()
{
    RunPartialSortTest();
    RunQuickSortTest();
    return 0;
}