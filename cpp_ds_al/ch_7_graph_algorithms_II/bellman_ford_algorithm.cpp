#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

struct Edge
{
    int src, dst, weight;
};

const int g_unknown = INT_MAX;

std::vector<int> BellmanFord(std::vector<Edge> edges, int v, int start)
{
    std::vector<int> distances(v--, g_unknown);
    distances[start] = 0;

    while(v--)
        for(auto& edge : edges)
            if(distances[edge.src] != g_unknown)
                distances[edge.dst] = std::min(distances[edge.dst]
                    , distances[edge.src] + edge.weight);
    
    for(auto& edge : edges)
        if(distances[edge.src] != g_unknown
        && distances[edge.dst] > distances[edge.src] + edge.weight)
        {
            std::cout << "Detect negative weight cycle!" << std::endl;
            return {};
        }

    return distances;
}

int main()
{
    int v = 6;
    std::vector<Edge> edges;

    std::vector<std::vector<int>> edge_map
    {
        {0, 1, 3},
        {1, 3, -8},
        {2, 1, 3},
        {2, 5, 5},
        {3, 2, 3},
        {2, 4, 2},
        {4, 5, -1},
        {5, 1, 8}
    };

    for(auto& edge : edge_map)
        edges.emplace_back(Edge {edge[0], edge[1], edge[2]});

    int start = 0;
    std::vector<int> distances = BellmanFord(edges, v, start);

    if(!distances.empty())
    {
        std::cout << "The shortest path from vertex [" << start << ']' << std::endl;

        for(int i = 0; i < distances.size(); ++i)
            if(distances[i] == g_unknown) std::cout << "Vertex " << i << ": not visited!" << std::endl;
            else std::cout << "Vertex " << i << ": " << distances[i] << std::endl;
    }
    return 0;
}