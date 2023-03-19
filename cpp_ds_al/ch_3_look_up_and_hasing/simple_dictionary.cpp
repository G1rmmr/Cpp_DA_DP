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