#include <iostream>
#include <queue>
#include <vector>

struct Median
{
    std::priority_queue<int> MaxHeap;
    std::priority_queue<int, std::vector<int>
    , std::greater<int>> MinHeap;

    void Insert(int data)
    {
        if(MaxHeap.size() == 0)
        {
            MaxHeap.push(data);
            return;
        }

        if(MaxHeap.size() == MinHeap.size())
        {
            if(data <= get()) MaxHeap.push(data);
            else MinHeap.push(data);

            return;
        }

        if(MaxHeap.size() < MinHeap.size())
        {
            if(data > get())
            {
                MaxHeap.push(MinHeap.top());
                MinHeap.pop();
                MinHeap.push(data);
            }
            else MaxHeap.push(data);
            return;
        }

        if(data < get())
        {
            MinHeap.push(MaxHeap.top());
            MaxHeap.pop();
            MaxHeap.push(data);
        }
        else MinHeap.push(data);
    }

    double get()
    {
        if(MaxHeap.size() == MinHeap.size())
            return (MaxHeap.top() + MinHeap.top()) / 2.0;

        if(MaxHeap.size() < MinHeap.size())
            return MinHeap.top();

        return MaxHeap.top();
    }
};

int main()
{
    Median Median;

    Median.Insert(1);
    std::cout << "The median after <1> insert: " << Median.get() << std::endl;

    Median.Insert(5);
    std::cout << "The median after <5> insert: " << Median.get() << std::endl;

    Median.Insert(2);
    std::cout << "The median after <2> insert: " << Median.get() << std::endl;

    Median.Insert(10);
    std::cout << "The median after <10> insert: " << Median.get() << std::endl;

    Median.Insert(40);
    std::cout << "The median after <40> insert: " << Median.get() << std::endl;
    
    return 0;
}