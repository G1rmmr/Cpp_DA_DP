#include <iostream>
#include <sstream>
#include <algorithm>

template <typename T>

class dynamic_array
{
    T* data;
    size_t n;

public:
    dynamic_array(int n)
    {
        this->n = n;
        data = new T[n];
    }
    //1. const study
    dynamic_array(const dynamic_array<T>& other)
    {
        n = other.n;
        data = new T[n];

        for(int i = 0; i < n; i++)
            data[i] = other[i];
    }

    //2. operator study
    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    T& at(int index)
    {
        if(index < n)
            return data[index];
        throw "Index out of range";
    }

    size_t size() const
    {
        return n;
    }

    ~dynamic_array()
    {
        delete[] data;
    }

    T* begin(){return data;}
    const T* begin() const{return data;}
    T* end(){return data + n;}
    const T* end() const{return data + n;}

    dynamic_array<T> friend operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
    {
        dynamic_array<T> result(arr1.size() + arr2.size());
        std::copy(arr1.begin(), arr1.end(), result.begin());
        std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());
        //3. copy study

        return result;
    }

    std::string to_string(const std::string& sep = ", ")
    {
        if(n == 0) return "";
            
        //4. ostringstream study
        std::ostringstream os;
        os << data[0];

        for (int i = 1; i < n; i++)
            os << sep << data[i];

        return os.str();
    }
};

struct student
{
    std::string name;
    int standard;
};

std::ostream& operator<<(std::ostream& os, const student& s)
{
    return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
    int nStudents;
    std::cout << "Enter the number of student in class 1: ";
    std::cin >> nStudents;

    dynamic_array<student> class1(nStudents);
    for (int i = 0; i < nStudents; i++)
    {
        std::string name;
        int standard;

        std::cout << "Enter a age and name of student number " << i + 1 << ": ";
        std::cin >> name >> standard;

        class1[i] = student{name, standard};
    }

    try
    {
        class1.at(nStudents) = student{"John", 8};
    }
    catch(...)
    {
        std::cout << "Exception catch!" << std::endl;
    }
    
    auto class2 = class1;
    std::cout << "Generate class 2 with copy of class 1: " << class2.to_string() << std::endl;

    auto class3 = class1 + class2;
    std::cout << "Genarate class 3 with merge class 1 and class 2: " << class3.to_string() << std::endl;

    return 0;
}