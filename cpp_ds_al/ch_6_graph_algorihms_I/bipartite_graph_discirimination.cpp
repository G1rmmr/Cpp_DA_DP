#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>

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
    Graph<T> graph(10);
    std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;

    edge_map[1] = {{2, 0}};
    edge_map[2] = {{1, 0}, {3, 0}, {8, 0}};
    edge_map[3] = {{2, 0}, {4, 0}};
    edge_map[4] = {{3, 0}, {6, 0}};
    edge_map[5] = {{7, 0}, {9, 0}};
    edge_map[6] = {{4, 0}};
    edge_map[7] = {{5, 0}};
    edge_map[8] = {{2, 0}, {9, 0}};
    edge_map[9] = {{5, 0}, {8, 0}};

    for(auto& edge : edge_map)
        for(auto& e : edge.second)
            graph.AddEdge(Edge<T>{edge.first, e.first, e.second});

    return graph;
}

template <typename T>
auto DFS(const Graph<T>& graph, unsigned start)
{
    std::stack<unsigned> stack;
    std::set<unsigned> visited;
    std::vector<unsigned> visit_order;
    std::vector<std::string> colors(graph.Vertices(), "None");

    auto pre_vertex = start;
    colors[start] = "Red";
    stack.push(start);

    while(!stack.empty())
    {
        auto current_vertex = stack.top();
        stack.pop();

        colors[current_vertex] = colors[pre_vertex] == "Black" ? "Red" : "Black";

        if(visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            visit_order.emplace_back(current_vertex);

            for(auto& edge : graph.Edges(current_vertex))
                if(visited.find(edge.dst) == visited.end())
                    stack.push(edge.dst);
        }
        pre_vertex = current_vertex;
    }
    std::vector<std::pair<unsigned, std::string>> visit_colors;

    for(auto& vertex : visit_order)
        visit_colors.emplace_back(std::make_pair(vertex, colors[vertex]));

    return visit_colors;
}

void IsBipartite(std::vector<std::pair<unsigned, std::string>> visit_colors)
{
    bool is_bipartite = true;

    for(auto& vertex : visit_colors)
    {
        std::cout << "Vertex " << vertex.first << ": " << vertex.second << std::endl;
        if(vertex.second == "None") is_bipartite = false; 
    }

    std::cout << (is_bipartite ? "The graph is bipartited." 
        : "The graph isn't bipartited.") << std::endl;
}

int main()
{
    using T = unsigned;
    auto graph = CreateRefGraph<T>();

    std::cout << "[Inputed graph]" << std::endl;
    std::cout << graph << std::endl;

    auto visit_colors = DFS(graph, 1);
    IsBipartite(visit_colors);

    return 0;
}