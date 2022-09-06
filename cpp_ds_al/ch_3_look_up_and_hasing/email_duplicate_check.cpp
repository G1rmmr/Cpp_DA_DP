#include <iostream>
#include <string>
#include <vector>

class DuplicateChecker
{
    std::vector<bool> Datas;
    int num_bits;

    int Hash(int num, std::string address)
    {
        int key = address.size();

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

    bool LookUp(std::string address)
    {
        bool bit_result 
        = Datas[Hash(0, address)] & Datas[Hash(1, address)] & Datas[Hash(2, address)];

        if(bit_result)
        {
            std::cout << address << ": This address is not available." << std::endl;
            return false;
        }
        else
        {
            std::cout << address << ": available address!" << std::endl;
            return true;
        } 
    }

    void Insert(std::string address)
    {
        if(LookUp(address))
        {
            Datas[Hash(0, address)] = true;
            Datas[Hash(1, address)] = true;
            Datas[Hash(2, address)] = true;

            std::cout << "Sign up with E-mail address <" 
            << address << "> has been completed!" << std::endl;
        }
    }
};

int main()
{
    DuplicateChecker Checker(16);

    Checker.Insert("blackhand2413@naver.com");
    Checker.Insert("blckhnd.std@gmail.com");
    Checker.Insert("blackhand2413@gmail.com");

    return 0;
}