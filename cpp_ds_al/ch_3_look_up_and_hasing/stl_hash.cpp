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

int main()
{
    std::cout << "*** STL Set examples ***" << std::endl;
    std::unordered_set<int> Set = {1, 2, 3, 4, 5};

    std::cout << "Set initialized value: ";
    Print(Set);

    Set.insert(2);

    std::cout << "Value <2> inserted: ";
    Print(Set);

    Set.insert(10);
    Set.insert(300);

    std::cout << "Value <10, 300> inserted: ";
    Print(Set);

    Find(Set, 4);
    Find(Set, 100);

    Set.erase(2);

    std::cout << "Value <2> erased: ";
    Print(Set);

    Find(Set, 2);

    std::cout << "*** STL Map examples ***" << std::endl;
    std::unordered_map<int, int> SquareMap;

    SquareMap.insert({2, 4});
    SquareMap[3] = 9;

    std::cout << "Square of <2, 3> inserted: ";
    Print(SquareMap);

    SquareMap[20] = 400;
    SquareMap[30] = 900;

    std::cout << "Square of <20, 30> inserted: ";
    Print(SquareMap);

    Find(SquareMap, 10);
    Find(SquareMap, 20);

    std::cout << "SquareMap[3] = " << SquareMap[3] << std::endl; 
    std::cout << "SquareMap[100] = " << SquareMap[100] << std::endl;

    Print(SquareMap);
    return 0;
}