#include <iostream>
#include <queue>

struct Node
{
    std::string position;
    Node* First;
    Node* Second;
};

struct OrganizationTree
{
    Node* Root;

    static OrganizationTree CreateOranization(const std::string& position)
    {
        OrganizationTree Tree;
        Tree.Root = new Node{position, NULL, NULL};
        return Tree;
    }

    static Node* Find(Node* Root, const std::string& target)
    {
        if(Root == NULL) return NULL;
        if(Root->position == target) return Root;

        auto first_found = OrganizationTree::Find(Root->First, target);
        if(first_found != NULL) return first_found;

        return OrganizationTree::Find(Root->Second, target);
    }

    bool AddSubOrdinate(const std::string& manager, const std::string& sub_ordinate)
    {
        auto manager_node = OrganizationTree::Find(Root, manager);

        if(!manager_node)
        {
            std::cout << "Can't find " << manager << " at chart." << std::endl;
            return false;
        }

        if(manager_node->First && manager_node->Second)
        {
            std::cout << "Can't add " << sub_ordinate << " under the " << manager << '.' << std::endl;
            return false;
        }

        if(!manager_node->First) manager_node->First = new Node{sub_ordinate, NULL, NULL};
        else manager_node->Second = new Node{sub_ordinate, NULL, NULL};

        std::cout << "Adding " << sub_ordinate << " under " << manager << " is sucessed." << std::endl;
        return true;
    }

    static void PreOrder(Node* start)
    {
        if(!start) return;

        std::cout << start->position << ", ";
        PreOrder(start->First);
        PreOrder(start->Second);
    }

    static void InOrder(Node* start)
    {
        if(!start) return;

        InOrder(start->First);
        std::cout << start->position << ", ";
        InOrder(start->Second);
    }

    static void PostOrder(Node* start)
    {
        if(!start) return;

        PostOrder(start->First);
        PostOrder(start->Second);
        std::cout << start->position << ", ";
    }

    static void LevelOrder(Node* start)
    {
        if(!start) return;

        std::queue<Node*> Queue;
        Queue.push(start);

        while(!Queue.empty())
        {
            int size = Queue.size();

            for(int i = 0; i < size; ++i)
            {
                auto current_node = Queue.front();
                Queue.pop();

                std::cout << current_node->position << ", ";
                
                if(current_node->First) Queue.push(current_node->First);
                if(current_node->Second) Queue.push(current_node->Second);
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    auto tree = OrganizationTree::CreateOranization("CEO");

    tree.AddSubOrdinate("CEO", "Vice president");

    tree.AddSubOrdinate("Vice president", "IT Director");
    tree.AddSubOrdinate("Vice president", "Marketing manager");

    tree.AddSubOrdinate("IT Director", "Security team leader");
    tree.AddSubOrdinate("IT Director", "Application development team leader");

    tree.AddSubOrdinate("Marketing manager", "Logistics team leader");
    tree.AddSubOrdinate("Marketing manager", "PR team leader");

    tree.AddSubOrdinate("Vice president", "Treasurer");
    std::cout << std::endl;

    OrganizationTree::PreOrder(tree.Root);
    std::cout << std::endl;

    OrganizationTree::InOrder(tree.Root);
    std::cout << std::endl;

    OrganizationTree::PostOrder(tree.Root);
    std::cout << std::endl;

    OrganizationTree::LevelOrder(tree.Root);
    return 0;
}