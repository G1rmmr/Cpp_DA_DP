#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
auto ComputeWaitingTimes(std::vector<T>& service_times)
{
    std::vector<T> w(service_times.size());
    w[0] = 0;

    for(auto i = 1; i < service_times.size(); ++i)
        w[i] = w[i - 1] + service_times[i - 1];

    return w;
}

template <typename T>
void PrintVector(std::vector<T>& v)
{
    for(auto e : v)
    {
        std::cout.width(2);
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void ComputeAndPrintWaitingTimes(std::vector<T>& service_times)
{
    auto waiting_times = ComputeWaitingTimes<int>(service_times);

    std::cout << "- Service time: ";
    PrintVector<T>(service_times);

    std::cout << "- Waiting time: ";
    PrintVector<T>(waiting_times);

    auto avg_waiting_times = std::accumulate(waiting_times.begin()
        , waiting_times.end(), 0.0) / waiting_times.size();

    std::cout << "- Average waiting time: " << avg_waiting_times << std::endl;
}