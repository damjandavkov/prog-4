#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> > ad_l(int n, vector<pair<int, int> > edges)
{
    vector<vector<int> > ans(n);
    for (auto e : edges)
    {
        ans[e.first].push_back(e.second);
        ans[e.second].push_back(e.first);
    }
    return ans;
}
vector<vector<bool> > ad_m(int n, vector<pair<int, int> > edges)
{
    vector<vector<bool> > ans(n, vector<bool>(n, 0));
    for (auto e : edges)
        ans[e.first][e.second] = ans[e.second][e.first] = 1;
    return ans;
}
/*int main()
{
    int n = 5;
    vector<pair<int, int> > edges = {{0, 1}, {1, 2}, {0, 2}, {3, 4}};
    vector<vector<int> > List = ad_l(n, edges);
    vector<vector<bool> > Matrix = ad_m(n, edges);
    for (auto a : List)
    {
        for (auto b : a)
            cout << b << ' ';
        cout << '\n';
    }
    cout << '\n';
    for (auto a : Matrix)
    {
        for (auto b : a)
            cout << b << ' ';
        cout << '\n';
    }
}*/
