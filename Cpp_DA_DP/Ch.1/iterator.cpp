#include <iostream>
#include <forward_list>
#include <vector>

using namespace std;

int main()
{
    vector<string> vec = {
        "Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
        "Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
        "Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
    };

    auto it = vec.begin();
    cout << "Latest winner: " << *it << endl;

    it += 8;
    cout << "Winner when 8 years ago: " << *it << endl;

    advance(it, -3);
    cout << "and winner after 3 years: " << *it << endl;

    forward_list<string> fwd(vec.begin(), vec.end());

    auto it1 = fwd.begin();
    cout << "Latest winner: " << *it1 << endl;

    advance(it1, 5);
    cout << "Winner when 5 years ago: " << *it1 << endl;

    return 0;
}