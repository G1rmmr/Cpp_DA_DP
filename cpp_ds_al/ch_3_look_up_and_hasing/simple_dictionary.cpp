#include <iostream>
#include <vector>

using uint = unsigned int;

class HashMap
{
    std::vector<int> Datas;

public:
    HashMap(size_t num)
    {
        Datas = std::vector<int>(num, -1);
    }

    void Insert(uint target)
    {   
        int num = Datas.size();
        Datas[target % num] = target;
        std::cout << "Data <" << target << "> inserted." << std::endl;
    }

    bool Find(uint target)
    {
        int num = Datas.size();
        return (Datas[target % num] == target);
    }

    void Erase(uint target)
    {
        int num = Datas.size();

        if(Datas[target % num] == target)
        {
            Datas[target % num] = -1;
            std::cout << "Data <" << target << "> erased." << std::endl;
        }
    }
};

int main()
{
    HashMap Map(7);

    auto Print = [&](int target)
    {
        if(Map.Find(target)) std::cout << "Find <" << target << "> from Checker.";
        else std::cout << "Can't find <" << target << "> from Checker.";
        std::cout << std::endl;
    };

    Map.Insert(2);
    Map.Insert(25);
    Map.Insert(10);

    Print(25);

    Map.Insert(100);

    Print(100);
    Print(2);

    Map.Erase(25);
    return 0;
}