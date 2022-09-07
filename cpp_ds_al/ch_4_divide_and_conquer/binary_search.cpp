#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

bool LinearSearch(int num, std::vector<int>& Sequence)
{
    for(auto e : Sequence)
        if(e == num) return true;

    return false;
}

bool BinarySearch(int num, std::vector<int>& Sequence)
{
    auto left = Sequence.begin(), right = Sequence.end();

    while(true)
    {
        auto range = std::distance(left, right);
        auto middle_index = left + std::floor(range / 2);
        auto mid = *(left + middle_index);

        if(mid == num) return true;
        if(mid > num) std::advance(right, -middle_index);
        if(mid < num) std::advance(left, middle_index);

        if(range == 1) return false;
    }
}

void RunSmallTest()
{
    auto num = 2;
    std::vector<int> Sequence = {1, 3, 2, 4, 5, 7, 9, 8, 6};

    std::sort(Sequence.begin(), Sequence.end());

    if(LinearSearch(num, Sequence)) std::cout << "Find element by linear search!" << std::endl;
    else std::cout << "Can't find element by linear search!" << std::endl;

    if(BinarySearch(num, Sequence)) std::cout << "Find element by binary search!" << std::endl;
    else std::cout << "Can't find element by binary search!" << std::endl;
}

void RunLargeTest(int size, int num)
{
    std::vector<int> Sequence;
    std::random_device Device;
    std::mt19937 rand(Device());

    std::uniform_int_distribution<std::mt19937::result_type> Dist(1, size);
    for(auto i = 0; i < size; ++i) Sequence.push_back(Dist(rand));
    std::sort(Sequence.begin(), Sequence.end());

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool search_result = BinarySearch(num, Sequence);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Binary search operation time: " << diff.count() << std::endl;

    if(search_result) std::cout << "Find element by binary search!" << std::endl;
    else std::cout << "Can't find element by binary search!" << std::endl;
}

int main()
{
    RunSmallTest();

    RunLargeTest(100000, 36543);
    RunLargeTest(1000000, 36543);
    RunLargeTest(10000000, 36543);

    return 0;
}