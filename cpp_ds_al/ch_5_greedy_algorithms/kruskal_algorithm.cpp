#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

class SimpleDisjointSet
{
private:
    struct Node
    {
        unsigned id, rank, parent;

        Node(unsigned _id) : id(_id), rank(0), parent(_id) {}

        bool operator != (const Node& node) const
        {
            return this->id != node.id;
        }
    };

    std::vector<Node> nodes;

public:
    SimpleDisjointSet(unsigned num){nodes.reserve(num);}
    void MakeSet(const unsigned& x){nodes.emplace_back(x);}

    unsigned Find(unsigned x)
    {
        auto node_iter = std::find_if(nodes.begin(), nodes.end()
            , [x](auto node){return node.id == x;});

        unsigned node_id = (*node_iter).id;

        while(node_id != nodes[node_id].parent)
            node_id = nodes[node_id].parent;

        return node_id;
    }

    void UnionSets(unsigned x, unsigned y)
    {
        auto root_x = Find(x), root_y = Find(y);
        if(root_x == root_y) return;

        if(nodes[root_x].rank > nodes[root_y].rank)
            std::swap(root_x, root_y);

        nodes[root_x].parent = nodes[root_y].parent;
        nodes[root_y].rank++;
    }
};

template <typename T>
struct Edge
{
    unsigned src, dst;
    T weight;

    inline bool operator< (const Edge<T>& edge) const
    {
        return this->weight < edge.weight;
    }

    inline bool operator> (const Edge<T>& edge) const
    {
        return this->weight > edge.weight;
    }
};

template <typename T>
class Graph
{
public:
    Graph(unsigned num) : num_of_vertices(num){}

    auto Vertices() const{return num_of_vertices;}
    auto& Edges() const{return edge_list;}

    auto Edges(unsigned vertex) const
    {
        std::vector<Edge<T>> edge_from_vertex;

        for(auto& edge : edge_list)
            if(edge.src == vertex)
                edge_from_vertex.emplace_back(edge);

        return edge_from_vertex;
    }

    void AddEdge(Edge<T>&& edge)
    {
        if(1 <= edge.src && edge.src <= num_of_vertices 
        && 1 <= edge.dst && edge.dst <= num_of_vertices)
            edge_list.emplace_back(edge);

        else std::cerr << "ERROR: vertex OUT OF RANGE!" << std::endl;
    }

    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, const Graph<U>& graph);

private:
    unsigned num_of_vertices;
    std::vector<Edge<T>> edge_list;
};

template <typename U>
std::ostream& operator<< (std::ostream& os, const Graph<U>& graph)
{
    for(unsigned i = 1; i < graph.Vertices(); ++i)
    {
        os << i << ":\t";

        auto edges = graph.Edges(i);

        for(auto& edge : edges)
            os << '{' << edge.dst << ": " << edge.weight << "}, ";

        os << std::endl;
    }
    return os;
}

template <typename T>
Graph<T> MinimumSpanningTree(const Graph<T>& graph)
{
    std::priority_queue<Edge<T>, std::vector<Edge<T>>
        , std::greater<Edge<T>>> edge_min_heap;

    for(auto& edge : graph.Edges()) edge_min_heap.push(edge);

    auto num = graph.Vertices();

    SimpleDisjointSet dset(num);
    for(unsigned i = 0; i < num; ++i) dset.MakeSet(i);

    Graph<T> MST(num);

    while(!edge_min_heap.empty())
    {
        auto edge = edge_min_heap.top();
        edge_min_heap.pop();

        if(dset.Find(edge.src) != dset.Find(edge.dst))
        {
            MST.AddEdge(Edge <T>{edge.src, edge.dst, edge.weight});
            dset.UnionSets(edge.src, edge.dst);
        }
    }
    return MST;
}