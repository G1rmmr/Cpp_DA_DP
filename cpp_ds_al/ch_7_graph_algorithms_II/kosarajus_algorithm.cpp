#include <vector>
#include <stack>
#include <iostream>

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
    int v = 9;
    std::vector<std::vector<int>> adj
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

    std::cout << "The number of strongly connected components: "
        << connected_components.size() << std::endl;

    for(int i = 0; i < connected_components.size(); ++i)
    {
        std::cout << '[' << i + 1 << "] ";

        for(auto& node : connected_components[i])
            std::cout << node << ' ';
        
        std::cout << std::endl;
    }
}