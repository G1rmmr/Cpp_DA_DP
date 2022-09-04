#include <iostream>
#include <string>
#include <vector>

struct Node
{
    bool is_file;
    std::string path_name;
};

struct NTree
{
public:
    Node* Root = new Node{false, "/"};
    std::vector<NTree*> Children;
    
    Node* Find(std::string path){return FindImple(Root, path);}

    void Insert(std::string path)
    {
        if(!Root) Root = new Node{(path[0] == '/' ? false : true), path};
        else InsertImple(Root, path);
    }

    void LevelOrder(){LevelOrderImple(Root);}

private:
    Node* FindImple(Node* current, std::string target)
    {
        if(!current)
        {
            std::cout << std::endl;
            return NULL;
        }

        if(current->path_name == target)
        {
            std::cout << target << " Find!" << std::endl;
            return current;
        }

        if(find(current->children.begin(), current->children.end(), target)
        != current->children.end())
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

    void InOrderImple(Node* start)
    {
        if(!start) return;

        InOrderImple(start->Left);
        std::cout << start->data << ' ';
        InOrderImple(start->Right);
    }
};
