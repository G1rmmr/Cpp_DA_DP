#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>

template <typename T>
struct Edge
{
    unsigned src, dst;
    T weight;
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
auto CreateRefGraph()
{
    Graph<T> graph(9);
    std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;

    edge_map[1] = {{2, 2}, {5, 3}};
    edge_map[2] = {{1, 2}, {5, 5}, {4, 1}};
    edge_map[3] = {{4, 2}, {7, 3}};
    edge_map[4] = {{2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5}};
    edge_map[5] = {{1, 3}, {2, 5}, {4, 2}, {8, 3}};
    edge_map[6] = {{4, 4}, {7, 4}, {8, 1}};
    edge_map[7] = {{3, 3}, {6, 4}};
    edge_map[8] = {{4, 5}, {5, 3}, {6, 1}};

    for(auto& edge : edge_map)
        for(auto& e : edge.second)
            graph.AddEdge(Edge<T>{edge.first, e.first, e.second});

    return graph;
}

template <typename T>
struct Label
{
    unsigned id;
    T distance;

    inline bool operator> (const Label<T>& label) const
    {
        return this->distance > label.distance;
    }
};

template <typename T>
auto PrimMST(const Graph<T>& graph, unsigned src)
{
    std::priority_queue<Label<T>, std::vector<Label<T>>, std::greater<Label<T>>> heap;
    std::vector<T> distance(graph.Vertices(), std::numeric_limits<T>::max());

    std::set<unsigned> visited;
    std::vector<unsigned> mst;

    heap.emplace(Label<T>{src, 0});

    while(!heap.empty())
    {
        auto current_vertex = heap.top();
        heap.pop();

        if(visited.find(current_vertex.id) == visited.end())
        {
            mst.emplace_back(current_vertex.id);
            
            for(auto& edge : graph.Edges(current_vertex.id))
            {
                auto neighbor = edge.dst, new_distance = edge.weight;

                if(new_distance < distance[neighbor])
                {
                    heap.emplace(Label<T>{neighbor, new_distance});
                    distance[neighbor] = new_distance;
                }
            }
            visited.insert(current_vertex.id);
        }
    }
    return mst;
}

int main()
{
    using T = unsigned;
    auto graph = CreateRefGraph<T>();

    std::cout << "[Inputed graph]" << std::endl;
    std::cout << graph << std::endl;

    auto mst = PrimMST(graph, 1);

    std::cout << "[MST]" << std::endl;

    for(auto vertex : mst) std::cout << vertex << std::endl;
    std::cout << std::endl;

    return 0;
}