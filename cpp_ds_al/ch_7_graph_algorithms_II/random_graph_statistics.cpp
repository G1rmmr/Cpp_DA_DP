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

int g_num_invalid_graph = 0, g_num_interesting_graph = 0;

static unsigned long int rand_next = 1;

int rand()
{
    rand_next = rand_next * 1103515245 + 12345;
    return (unsigned int)(rand_next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    rand_next = seed;
}

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

    if(HasNegativeCycle(edges, distances)) return {};
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

    if(h.empty())
    {
        g_num_invalid_graph++;
        return;
    }

    for(auto& edge : edges)
        edge.weight += (h[edge.src] - h[edge.dst]);

    std::vector<std::vector<int>> shorest(v);

    for(int i = 0; i < v; ++i)
        shorest[i] = Dijstra(edges, v, i);

    for(int i = 0; i < v; ++i)
        for(int j = 0; j < v; ++j)
            if(shorest[i][j] == g_unknown)
                g_num_invalid_graph++;
}

int main()
{
    int seed, iter, v, e;
    std::cin >> seed >> iter >> v >> e;

    while(iter--)
    {
        std::vector<Edge> edges;
        srand(seed);

        for(int i = 0; i < v; ++i)
        {
            int source = rand(), destination = rand(), weight = rand();
            if(!rand() % 3) weight = -weight;

            edges.emplace_back(Edge {source, destination, weight});
        }
        Johnson(edges, v);
    }
    
    std::cout << "The number of invalid graph: " 
        << g_num_invalid_graph << std::endl;

    std::cout << "The rate of interesting graph generation" 
        << std::endl;

    return 0;
}