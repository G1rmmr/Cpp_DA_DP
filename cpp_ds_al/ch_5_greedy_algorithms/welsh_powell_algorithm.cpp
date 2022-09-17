#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

std::unordered_map<unsigned, std::string> color_map = {
    {1, "Red"}, {2, "Blue"}, {3, "Green"}
    , {4, "Yellow"}, {5, "Black"}, {6, "White"}
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
auto WelshPowellColoring(Graph<T>& graph)
{
    auto size = graph.Vertices();
    std::vector<unsigned> assigned_colors;

    graph = SortGraph(graph);

    for(unsigned i = 1; i < size; ++i)
    {
        auto outgoing_edges = graph.Edges(i);
        std::set<unsigned> neighbors;

        for(auto& edge : outgoing_edges)
            neighbors.insert(assigned_colors[edge.dst]);

        auto smallest = 1;

        for(; smallest <= color_map.size(); ++smallest)
            if(neighbors.find(smallest) == neighbors.end()) break;

        assigned_colors[i] = smallest;
    }
    return assigned_colors;
}

template <typename T>
bool CompareWithDegree(std::vector<Edge<T>> edge_1
, std::vector<Edge<T>> edge_2)
{
    return edge_1.size() > edge_2.size();
}

template <typename T>
auto SortGraph(const Graph<T>& graph)
{
    Graph<T> sorted_graph(graph.Vertices());
    std::vector<Edge<T>> temp_edges;

    for(unsigned i = 1; i < graph.Vertices(); ++i)
        temp_edges.emplace_back(graph.Edges(i));

    std::sort(temp_edges.begin(), temp_edges.end(), CompareWithDegree);

    std::cout << "[Coloring order (bracket means degree)]" << std::endl;
    
    for(auto& edge : temp_edges)
        std::cout << edge.src << " (" << edge.size() << ')' << std::endl;

    for(auto& edge : temp_edges) sorted_graph.AddEdge(edge);
    return sorted_graph;
}

template <typename T>
void PrintColors(std::vector<T>& colors)
{
    for(auto color = 1; color < colors.size(); ++color)
        std::cout << color << ": " << color_map[colors[color]] << std::endl;
}

int main()
{
    using T = unsigned;
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

    std::cout << "[Inputed graph]" << std::endl;
    std::cout << graph << std::endl;

    auto colors = WelshPowellColoring<T>(graph);

    std::cout << "[Graph coloring]" << std::endl;
    PrintColors(colors);

    return 0;
}