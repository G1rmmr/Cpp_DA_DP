#include <iostream>
#include <vector>

enum class City : int
{
    MOSCOW, LONDON, SEOUL, SEATTLE, DUBAI, SYDNEY
};

std::ostream& operator<<(std::ostream& os, const City c)
{
    switch(c)
    {
        case City::MOSCOW:
            os << "Moscow";
            return os;

        case City::LONDON:
            os << "London";
            return os;

        case City::SEOUL:
            os << "Seoul";
            return os;

        case City::SEATTLE:
            os << "Seattle";
            return os;

        case City::DUBAI:
            os << "Dubai";
            return os;

        case City::SYDNEY:
            os << "Sydney";
            return os;

        default:
            return os;
    }
}

struct Graph
{
    std::vector<std::vector<int>> Data;

    Graph(int num)
    {
        Data.reserve(num);
        std::vector<int> row(num);
        std::fill(row.begin(), row.end(), -1);

        for(int i = 0; i < num; ++i)
            Data.push_back(row);
    }

    void AddEdge(const City city_1, const City city_2, int distance)
    {
        std::cout << "Add a edge: " 
        << city_1 << " - " << city_2 << " = " << distance
        << std::endl;

        auto num_1 = static_cast<int>(city_1), num_2 = static_cast<int>(city_2);
        Data[num_1][num_2] = distance;
        Data[num_2][num_1] = distance;
    }

    void RemoveEdge(const City city_1, const City city_2)
    {
        std::cout << "Remove a edge: " << city_1 << " - " << city_2 << std::endl;
        auto num_1 = static_cast<int>(city_1), num_2 = static_cast<int>(city_2);
        
        Data[num_1][num_2] = -1;
        Data[num_2][num_1] = -1;
    }
};

int main()
{
    Graph graph(6);

    graph.AddEdge(City::LONDON, City::MOSCOW, 2500);
    graph.AddEdge(City::LONDON, City::SEOUL, 9000);
    graph.AddEdge(City::LONDON, City::DUBAI, 5500);

    graph.AddEdge(City::SEOUL, City::MOSCOW, 6600);
    graph.AddEdge(City::SEOUL, City::SEATTLE, 8000);
    graph.AddEdge(City::SEOUL, City::DUBAI, 7000);
    graph.AddEdge(City::SEOUL, City::SYDNEY, 8000);

    graph.AddEdge(City::SEATTLE, City::MOSCOW, 8400);
    graph.AddEdge(City::SEATTLE, City::SYDNEY, 12000);
    graph.AddEdge(City::SEATTLE, City::LONDON, 8000);

    graph.RemoveEdge(City::SEATTLE, City::LONDON);
    return 0;
}