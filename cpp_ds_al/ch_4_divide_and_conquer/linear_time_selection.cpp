#include <iostream>
#include <vector>

template <typename T>
std::vector<T> Merge(std::vector<T>& arr1, std::vector<T>& arr2)
{
    std::vector<T> merged;

    auto iter1 = arr1.begin();
    auto iter2 = arr2.begin();

    while(iter1 != arr1.end() && iter2 != arr2.end())
    {
        if(*iter1 < *iter2) merged.emplace_back(*(iter1++));
        else merged.emplace_back(*(iter2++));
    }

    if(iter1 != arr1.end())
    {
        for(; iter1 != arr1.end(); ++iter1)
            merged.emplace_back(*iter1);
    }
    else
    {
        for(; iter2 != arr2.end(); ++iter2)
            merged.emplace_back(*iter2);
    }
    return merged;
}

template <typename T>
std::vector<T> MergeSort(std::vector<T> arr)
{
    if(arr.size() > 1)
    {
        auto mid = size_t(arr.size() / 2);
        auto left_half = MergeSort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
        auto right_half = MergeSort<T>(std::vector<T>(arr.begin() + mid, arr.end()));

        return Merge<T>(left_half, right_half);
    }
    return arr;
}

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
auto FindMedian(typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator last)
{
    QuickSort<T>(begin, last);
    return begin + (std::distance(begin, last) / 2);
}

template <typename T>
auto PartitionUsingGivenPivot(typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator end,
    typename std::vector<T>::iterator pivot)
{
    auto left_iter = begin;
    auto right_iter = end;

    while(true)
    {
        while(*left_iter <= *pivot && left_iter != right_iter)
            left_iter++;

        while(*right_iter > *pivot && left_iter != right_iter)
            right_iter--;

        if(left_iter == right_iter) break;
        else std::iter_swap(left_iter, right_iter);
    }

    if(*pivot > *right_iter) std::iter_swap(begin, right_iter);
    return right_iter;
}

template <typename T>
typename std::vector<T>::iterator LinearTimeSelect(
    typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator last,
    size_t i)
{
    auto size = std::distance(begin, last);

    if(size > 0 && i < size)
    {
        auto num_vi = (size + 4) / 5;
        size_t j = 0;

        std::vector<T> m;

        for(; j < size / 5; ++j)
        {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + 5;

            m.emplace_back(*FindMedian<T>(b, l));
        }

        if(j * 5 < size)
        {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + (size % 5);

            m.emplace_back(*FindMedian<T>(b, l));
        }

        auto median_of_medians = (m.size() == 1) ? m.begin() : 
            LinearTimeSelect<T>(m.begin(), m.end() - 1, m.size() / 2);

        auto partition_iter = PartitionUsingGivenPivot<T>(begin, last, median_of_medians);
        auto k = std::distance(begin, partition_iter) + 1;

        if(i == k) return partition_iter;
        else if(i < k) return LinearTimeSelect<T>(begin, partition_iter - 1, i);
        else if(i > k) return LinearTimeSelect<T>(partition_iter + 1, last, i - k);
    }
    else return begin;
}

template <typename T>
void PrintVector(std::vector<T> arr)
{
    for(auto e : arr) std::cout << e << ' ';
    std::cout << std::endl;
}

void RunLinearSelectTest()
{
    std::vector<int> s1{45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
    std::cout << "<Unsorted input vector>\n" << std::endl;

    PrintVector<int>(s1);
    std::cout << std::endl;

    std::cout << "<Now, all vectors are sorted>\n" << std::endl;
    PrintVector<int>(MergeSort<int>(s1));

    std::cout << std::endl;

    std::cout << "3rd element: " 
        << *LinearTimeSelect<int>(s1.begin(), s1.end() - 1, 3) << std::endl;

    std::cout << "5th element: " 
        << *LinearTimeSelect<int>(s1.begin(), s1.end() - 1, 5) << std::endl;

    std::cout << "11th element: " 
        << *LinearTimeSelect<int>(s1.begin(), s1.end() - 1, 11) << std::endl;
}