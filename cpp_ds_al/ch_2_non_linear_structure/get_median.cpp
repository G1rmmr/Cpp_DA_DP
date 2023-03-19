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