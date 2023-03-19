#include <iostream>

struct Node
{
    int data;
    Node* Left;
    Node* Right;
};

struct BST
{
public:
    Node* Root = nullptr;

    Node* Find(int target)
    {
        return FindImple(Root, target);
    }

    void Insert(int target)
    {
        if(!Root) Root = new Node{target, NULL, NULL};
        else InsertImple(Root, target);
    }

    void InOrder(){InOrderImple(Root);}

    void DeleteData(int target){Root = DeleteImple(Root, target);}

    Node* Success(Node* start)
    {
        auto current = start->Right;
        while(current && current->Left) current = current->Left;
        return current;
    }

private:
    Node* FindImple(Node* current, int target)
    {
        if(!current)
        {
            std::cout << std::endl;
            return NULL;
        }

        if(current->data == target)
        {
            std::cout << target << " Find!" << std::endl;
            return current;
        }

        if(target < current->data)
        {
            std::cout << "Search left node of " << current->data << ": ";
            return FindImple(current->Left, target);
        }

        std::cout << "Search right node of " << current->data << ": ";
        return FindImple(current->Right, target);
    }

    void InsertImple(Node* current, int target)
    {
        if(target < current->data)
        {
            if(!current->Left) current->Left = new Node{target, NULL, NULL};
            else InsertImple(current->Left, target);
        }
        else
        {
            if(!current->Right) current->Right = new Node{target, NULL, NULL};
            else InsertImple(current->Right, target);
        }
    }

    Node* DeleteImple(Node* start, int target)
    {
        if(!start) return NULL;

        if(target > start->data) start->Right = DeleteImple(start->Right, target);
        else if(target < start->data) start->Left = DeleteImple(start->Left, target);
        else
        {
            if(!start->Left)
            {
                auto temp_data = start->Right;
                delete start;
                return temp_data;
            }

            if(!start->Right)
            {
                auto temp_data = start->Left;
                delete start;
                return temp_data;
            }

            auto sucessed_node = Success(start);
            start->data = sucessed_node->data;
            start->Right = DeleteImple(start->Right, sucessed_node->data);
        }
        return start;
    }

    void InOrderImple(Node* start)
    {
        if(!start) return;

        InOrderImple(start->Left);
        std::cout << start->data << ' ';
        InOrderImple(start->Right);
    }
};