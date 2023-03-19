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
void PrintVector(std::vector<T> arr)
{
    for(auto e : arr) std::cout << e << ' ';
    std::cout << std::endl;
}

void RunMergeSortTest()
{
    std::vector<int> s1{45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};

    std::vector<float> s2{45.6f, 1.0f, 3.8f, 1.0f, 2.2f, 3.9f, 45.3f, 5.5f
                        , 1.0f, 2.0f, 44.0f, 5.0f, 7.0f};

    std::vector<double> s3{45.6, 1.0, 3.8, 1.0, 2.2, 3.9, 45.3, 5.5
                        , 1.0, 2.0, 44.0, 5.0, 7.0};

    std::vector<char> c{'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

    std::cout << "<Unsorted input vector>\n" << std::endl;

    PrintVector<int>(s1);
    PrintVector<float>(s2);
    PrintVector<double>(s3);
    PrintVector<char>(c);

    std::cout << std::endl;

    auto sorted_s1 = MergeSort<int>(s1);
    auto sorted_s2 = MergeSort<float>(s2);
    auto sorted_s3 = MergeSort<double>(s3);
    auto sorted_c = MergeSort<char>(c);

    std::cout << "<Now, all vectors are sorted>\n" << std::endl;

    PrintVector<int>(sorted_s1);
    PrintVector<float>(sorted_s2);
    PrintVector<double>(sorted_s3);
    PrintVector<char>(sorted_c);

    std::cout << std::endl;
}