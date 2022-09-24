#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <random>

struct Edge
{
    int src, dst, weight;
};

const int g_unknown = INT_MAX;

bool HasNegativeCycle(const std::vector<Edge>& edges, std::vector<int> distances)
{
    for(auto& edge : edges)
        if(distances[edge.src] != g_unknown
        && distances[edge.dst] > distances[edge.src] + edge.weight)
            return true;

    return false;
}

std::vector<int> BellmanFord(std::vector<Edge> edges, int v)
{
    std::vector<int> distances(v + 1, g_unknown);

    int start = v;
    for(int i = 0; i < v; ++i)
        edges.emplace_back(Edge {start, i, 0});

    distances[start] = 0;

    while(v--)
        for(auto& edge : edges)
            if(distances[edge.src] != g_unknown)
                distances[edge.dst] = std::min(distances[edge.dst]
                    , distances[edge.src] + edge.weight);

    if(HasNegativeCycle(edges, distances))
    {
        std::cout << "Detect negative weight cycle!" << std::endl;
        return {};
    }
    return distances;
}

int GetMinDistance(std::vector<int>& distances, std::vector<bool>& visited)
{
    int min_distance = g_unknown, min_index = -1;

    for(int i = 0; i < distances.size(); ++i)
        if(!visited[i] && distances[i] <= min_distance)
        {
            min_distance = distances[i];
            min_index = i;
        }
    return min_index;
}

std::vector<int> Dijstra(std::vector<Edge> edges, int v, int start)
{
    std::vector<int> distances(v, g_unknown);
    std::vector<bool> visited(v, false);

    distances[start] = 0;

    for(int i = 0; i < v - 1; ++i)
    {
        int cur = GetMinDistance(distances, visited);
        visited[cur] = true;

        for(auto& edge : edges)
            if(distances[cur] != g_unknown
            && edge.src == cur && !visited[edge.dst])
                distances[edge.dst] = std::min(distances[edge.dst]
                    , distances[cur] + edge.weight);
    }
    return distances;
}

void Johnson(std::vector<Edge> edges, int v)
{
    std::vector<int> h = BellmanFord(edges, v);

    if(h.empty()) return;

    for(auto& edge : edges)
        edge.weight += (h[edge.src] - h[edge.dst]);

    std::vector<std::vector<int>> shorest(v);

    for(int i = 0; i < v; ++i)
        shorest[i] = Dijstra(edges, v, i);

    for(int i = 0; i < v; ++i)
    {
        std::cout << i << ":\n";
        
        for(int j = 0; j < v; ++j)
            if(shorest[i][j] != g_unknown)
            {
                shorest[i][j] += h[j] - h[i];
                std::cout << "\t" << j << ": " << shorest[i][j] << std::endl;
            }
    }  
}

int main()
{
    int v = 5;
    std::vector<Edge> edges;

    std::vector<std::vector<int>> edge_map
    {
        {0, 1, 7},
        {1, 2, -2},
        {2, 0, 10},
        {0, 3, -5},
        {0, 4, 2},
        {3, 4, 4}
    };

    for(auto& edge : edge_map)
        edges.emplace_back(Edge {edge[0], edge[1], edge[2]});

    Johnson(edges, v);
    return 0;
}