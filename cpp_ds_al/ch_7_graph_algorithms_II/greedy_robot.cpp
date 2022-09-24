#include <vector>
#include <string>
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
            return {};

    return distances;
}

int main()
{
    int size;
    std::cin >> size;

    int v = size * size;
    std::vector<std::vector<int>> edge_map;

    for(int i = 0; i < v - 1; ++i)
    {
        std::string direction;
        int weight;

        std::cin >> direction >> weight;

        for(auto& e : direction)
        {
            std::vector<int> temp = {i};

            if(e == 'N') temp.emplace_back(i - size);
            else if(e == 'S') temp.emplace_back(i + size);
            else if(e == 'E') temp.emplace_back(i + 1);
            else temp.emplace_back(i - 1);

            temp.emplace_back(-weight);
            edge_map.emplace_back(temp);
        }
    }

    std::vector<Edge> edges;

    for(auto& edge : edge_map)
        edges.emplace_back(Edge {edge[0], edge[1], edge[2]});

    int start = 0;
    std::vector<int> distances = BellmanFord(edges, v, start);

    if(distances.empty()) std::cout << "Searching stop" << std::endl;
    else std::cout << -distances[v - 1] << std::endl;
    
    return 0;
}