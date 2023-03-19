#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;

class HashMap
{
    std::vector<std::list<int>> Datas;

public:
    HashMap(size_t num)
    {
        Datas.resize(num);
    }

    void Insert(uint target)
    {   
        int num = Datas.size();
        Datas[target % num].push_back(target);
        std::cout << "Data <" << target << "> inserted." << std::endl;
    }

    bool Find(uint target)
    {
        int num = Datas.size();
        auto& entries = Datas[target % num];

        return (std::find(entries.begin(), entries.end(), target) 
            != entries.end());
    }

    void Erase(uint target)
    {
        int num = Datas.size();
        auto& entries = Datas[target % num];
        auto iter = std::find(entries.begin(), entries.end(), target);

        if(iter != entries.end())
        {
            entries.erase(iter);
            std::cout << "Data <" << target << "> erased." << std::endl;
        }
    }
};