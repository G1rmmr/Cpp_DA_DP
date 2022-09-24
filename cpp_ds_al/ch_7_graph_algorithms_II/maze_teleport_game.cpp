#include <vector>
#include <stack>
#include <iostream>
#include <climits>

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

std::vector<std::vector<int>> Johnson(std::vector<Edge> edges, int v)
{
    std::vector<int> h = BellmanFord(edges, v);
    if(h.empty()) return {};

    for(auto& edge : edges)
        edge.weight += (h[edge.src] - h[edge.dst]);

    std::vector<std::vector<int>> shortest(v);

    for(int i = 0; i < v; ++i)
        shortest[i] = Dijstra(edges, v, i);

    for(int i = 0; i < v; ++i)
        for(int j = 0; j < v; ++j)
            if(shortest[i][j] != g_unknown)
                shortest[i][j] += h[j] - h[i];

    return shortest;
}

void FillStack(int node, std::vector<bool>& visited
    , std::vector<std::vector<int>>& adj, std::stack<int>& stack)
{
    visited[node] = true;

    for(auto& next : adj[node])
        if(!visited[next])
            FillStack(next, visited, adj, stack);

    stack.push(node);
}

std::vector<std::vector<int>> Transpose(int v, std::vector<std::vector<int>> adj)
{
    std::vector<std::vector<int>> transpose(v);

    for(int i = 0; i < v; ++i)
        for(auto& next : adj[i])
            transpose[next].emplace_back(i);

    return transpose;
}

void CollectConnectedComponents(int node, std::vector<bool>& visited
    , std::vector<std::vector<int>>& adj, std::vector<int>& component)
{
    visited[node] = true;
    component.emplace_back(node);

    for(auto& next : adj[node])
        if(!visited[next])
            CollectConnectedComponents(next, visited, adj, component);
}

std::vector<std::vector<int>> Kosaraju(int v, std::vector<std::vector<int>> adj)
{
    std::vector<bool> visited(v, false);
    std::stack<int> stack;

    for(int i = 0; i < v; ++i)
        if(!visited[i])
            FillStack(i, visited, adj, stack);

    std::vector<std::vector<int>> transpose = Transpose(v, adj);
    std::fill(visited.begin(), visited.end(), false);

    std::vector<std::vector<int>> connected_components;

    while(!stack.empty())
    {
        int node = stack.top();
        stack.pop();

        if(!visited[node])
        {
            std::vector<int> component;

            CollectConnectedComponents(node, visited, transpose, component);
            connected_components.emplace_back(component);
        }
    }
    return connected_components;
}

int main()
{
    int num_of_rooms, num_of_teleports;
    std::vector<std::vector<int>> adj

    while(num_of_teleports--)
    {
        std::vector<int> temp(3);

    }
    
    {
        {1, 3},
        {2, 4},
        {3, 5},
        {7},
        {2},
        {4, 6},
        {7, 2},
        {8},
        {3}
    };

    std::vector<std::vector<int>> connected_components = Kosaraju(v, adj);

    for(int i = 0; i < connected_components.size(); ++i)
    {
        for(auto& node : connected_components[i])
            std::cout << node << ' ';
        
        std::cout << std::endl;
    }
}