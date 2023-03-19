#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

template <typename T>
void PrintVector(std::vector<T> arr)
{
    for(auto e : arr) std::cout << e << ' ';
    std::cout << std::endl;
}

void TransformTest(std::vector<int> s)
{
    std::vector<int> transed;
    std::cout << "[Map test]" << std::endl;

    std::cout << "Inputed vector, s: ";
    PrintVector<int>(s);

    std::transform(s.begin(), s.end(), std::back_inserter(transed)
        , [](int x){return std::pow(x, 2.0);});

    std::cout << "std::transform(), transed: ";
    PrintVector<int>(transed);

    std::for_each(s.begin(), s.end(), [](int& x){x = std::pow(x, 2.0);});

    std::cout << "std::for_each(), s: ";
    PrintVector<int>(s);
}

void ReduceTest(std::vector<int> s)
{
    std::cout << std::endl << "[Reduce test]" << std::endl;

    std::cout << "Inputed vector, s: ";
    PrintVector<int>(s);

    auto ans = std::accumulate(s.begin(), s.end(), 0
        , [](int acc, int x){return acc + x;});

    std::cout << "std::accumulate(), s: " << ans << std::endl;
}