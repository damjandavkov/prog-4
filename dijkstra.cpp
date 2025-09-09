#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dijkstra(int n, vector<vector<int> > edges)
{
    vector<vector<pair<int, int> > > g(n);
    for (auto e : edges)
    {
        g[e[0]].push_back({e[1], e[2]});
        g[e[1]].push_back({e[0], e[2]});
    }
    const int INF = 2147483647;
    vector<int> di(n, INF);
    vector<bool> vi(n, 0);
    di[0] = 0;
    priority_queue<pair<int, int> > q;
    q.push({0, 0});
    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if (vi[a])
            continue;
        vi[a] = 1;
        for (auto e : g[a])
        {
            if (di[e.first] > di[a] + e.second)
            {
                di[e.first] = di[a] + e.second;
                q.push({-di[e.first], e.first});
            }
        }
    }
    return di[n - 1];
}
/*int main()
{
    int n = 5;
    vector<vector<int> > edges = {{0, 1, 3}, {1, 2, 3}, {0, 2, 7}, {2, 4, 9}, {1, 4, 9}};
    cout << dijkstra(n, edges);
}*/
