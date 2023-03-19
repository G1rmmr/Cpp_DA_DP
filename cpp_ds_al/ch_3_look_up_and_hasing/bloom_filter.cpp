#include <iostream>
#include <vector>

class DuplicateChecker
{
    std::vector<bool> Datas;
    int num_bits;

    int Hash(int num, int key)
    {
        switch(num)
        {
            case 0: return key % num_bits;
            case 1: return (key / 7) % num_bits;
            case 2: return (key / 11) % num_bits;
        }
        return 0;
    }

public:
    DuplicateChecker(int num) : num_bits(num)
    {
        Datas = std::vector<bool>(num_bits, false);
    }

    void LookUp(int key)
    {
        bool bit_result 
        = Datas[Hash(0, key)] & Datas[Hash(1, key)] & Datas[Hash(2, key)];

        if(bit_result) std::cout << key << ": probable value." << std::endl;
        else std::cout << key << ": never a value." << std::endl;
    }

    void Insert(int key)
    {
        Datas[Hash(0, key)] = true;
        Datas[Hash(1, key)] = true;
        Datas[Hash(2, key)] = true;

        std::cout << "A key <" << key << "> is inserted: ";
        for(auto e : Datas) std::cout << e << ' ';
        std::cout << std::endl;
    }
};