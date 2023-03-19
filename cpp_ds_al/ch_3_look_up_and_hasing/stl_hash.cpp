#include <iostream>
#include <unordered_map>
#include <unordered_set>

void Print(const std::unordered_set<int>& Container)
{
    for(const auto& element : Container) std::cout << element << ' ';
    std::cout << std::endl;
}

void Print(const std::unordered_map<int, int>& Container)
{
    for(const auto& element : Container)
        std::cout << element.first << " -> " << element.second << ", ";

    std::cout << std::endl;
}

void Find(const std::unordered_set<int>& Container, const int element)
{
    if(Container.find(element) == Container.end())
        std::cout << "Searching <"<< element << "> failed." << std::endl;

    else std::cout << "Searching <"<< element << "> successed." << std::endl;
}

void Find(const std::unordered_map<int, int>& Container, const int element)
{
    auto iter = Container.find(element);

    if(iter == Container.end())
        std::cout << "Searching <"<< element << "> failed." << std::endl;

    else std::cout << "Searching <"<< element << "> successed, value = <" 
    << iter->second << ">." << std::endl;
}