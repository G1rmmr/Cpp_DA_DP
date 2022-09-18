#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>

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

    edge_map[1] = {{2, 0}, {5, 0}};
    edge_map[2] = {{1, 0}, {5, 0}, {4, 0}};
    edge_map[3] = {{4, 0}, {7, 0}};
    edge_map[4] = {{2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0}};
    edge_map[5] = {{1, 0}, {2, 0}, {4, 0}, {8, 0}};
    edge_map[6] = {{4, 0}, {7, 0}, {8, 0}};
    edge_map[7] = {{3, 0}, {6, 0}};
    edge_map[8] = {{4, 0}, {5, 0}, {6, 0}};

    for(auto& edge : edge_map)
        for(auto& e : edge.second)
            graph.AddEdge(Edge<T>{edge.first, e.first, e.second});

    return graph;
}

template <typename T>
auto BFS(const Graph<T>& graph, unsigned start)
{
    std::queue<unsigned> queue;
    std::set<unsigned> visited;
    std::vector<unsigned> visit_order;

    queue.push(start);

    while(!queue.empty())
    {
        auto current_vertex = queue.front();
        queue.pop();

        if(visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            visit_order.emplace_back(current_vertex);

            for(auto& edge : graph.Edges(current_vertex))
                if(visited.find(edge.dst) == visited.end())
                    queue.push(edge.dst);
        }
    }
    return visit_order;
}

int main()
{
    using T = unsigned;
    auto graph = CreateRefGraph<T>();

    std::cout << "[Inputed graph]" << std::endl;
    std::cout << graph << std::endl;

    std::cout << "[BFS visit order]" << std::endl;
    auto bfs_visit_order = BFS(graph, 1);

    for(auto vertex : bfs_visit_order)
        std::cout << vertex << std::endl;

    return 0;
}