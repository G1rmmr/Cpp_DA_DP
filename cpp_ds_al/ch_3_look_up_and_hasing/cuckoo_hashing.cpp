#include <iostream>
#include <vector>

class HashMap
{
    std::vector<int> Datas1;
    std::vector<int> Datas2;
    int size;

    int Hash1(int key) const{return key % size;}
    int Hash2(int key) const{return (key / size) % size;}

public:
    HashMap(int num) : size(num)
    {
        Datas1 = std::vector<int>(num, -1);
        Datas2 = std::vector<int>(num, -1);
    }

    std::vector<int>::iterator LookUp(int key)
    {
        auto hash_value_1 = Hash1(key);

        if(Datas1[hash_value_1] == key)
        {
            std::cout << "Find value <" << key << ">." << std::endl;
            return Datas1.begin() + hash_value_1; 
        }

        auto hash_value_2 = Hash2(key);

        if(Datas2[hash_value_2] == key)
        {
            std::cout << "Find value <" << key << ">." << std::endl;
            return Datas2.begin() + hash_value_2; 
        }
        return Datas2.end();
    }

    void Insert(int key){InsertImple(key, 0, 1);}

    void InsertImple(int key, int count, int Checker_num)
    {   
        if(count >= size)
        {
            std::cout << "Cycle occurs when inserting a key <" << key << ">!" << std::endl;
            std::cout << "Rehasing is required!" << std::endl;
            return;
        }

        if(Checker_num == 1)
        {
            int hash = Hash1(key);

            if(Datas1[hash] == -1)
            {
                std::cout << "Key <" << key << "> inserted. in Checker <"
                << Checker_num << ">." << std::endl;

                Datas1[hash] = key;
            }
            else
            {
                int pre_key = Datas1[hash];
                Datas1[hash] = key;

                std::cout << "Key <" << key << "> inserted. in Checker <"
                << Checker_num << ">: Moved from <" << pre_key << ">."
                << std::endl << "->";

                InsertImple(pre_key, count + 1, 2);
            }
        }
        else
        {
            int hash = Hash2(key);

            if(Datas2[hash] == -1)
            {
                std::cout << "Key <" << key << "> inserted. in Checker <"
                << Checker_num << ">." << std::endl;

                Datas2[hash] = key;
            }
            else
            {
                int pre_key = Datas2[hash];
                Datas2[hash] = key;

                std::cout << "Key <" << key << "> inserted. in Checker <"
                << Checker_num << ">: Moved from <" << pre_key << ">."
                << std::endl << "->";

                InsertImple(pre_key, count + 1, 1);
            }
        }
    }

    void Print()
    {
        std::cout << "Index: ";
        for(int i = 0; i < size; ++i) std::cout << i << '\t';
        std::cout << std::endl;

        std::cout << "Datas1: ";
        for(auto e : Datas1) std::cout << e << '\t';
        std::cout << std::endl;

        std::cout << "Datas2: ";
        for(auto e : Datas2) std::cout << e << '\t';
        std::cout << std::endl;
    }

    void Erase(int key)
    {
        auto position = LookUp(key);

        if(position != Datas2.end())
        {
            *position = -1;
            std::cout << "The value of <" << key << "> erased." << std::endl;
        }
        else std::cout << "Can't find key <" << key << "> from Checker." << std::endl;
    }
};

int main()
{
    HashMap Map(7);
    Map.Print();

    std::cout << std::endl;

    Map.Insert(10);
    Map.Insert(20);
    Map.Insert(30);

    std::cout << std::endl;

    Map.Insert(104);
    Map.Insert(2);
    Map.Insert(70);
    Map.Insert(9);
    Map.Insert(90);
    Map.Insert(2);
    Map.Insert(7);

    std::cout << std::endl;

    Map.Print();
    std::cout << std::endl;

    Map.Insert(14);
    return 0;
}