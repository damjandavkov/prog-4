#include <iostream>
#include <vector>
using namespace std;
vector<int> dijkstra(int n)
{
    vector<int> p = {2}, q;
    int l = 1, sq = 4;
    for (int i = 3; i <= n; i += 2)
    {
        if (i >= sq)
        {
            q.push_back(sq);
            sq = p[l] * p[l];
            l++;
        }
        bool w = 1;
        for (int j = 1; j < l; j++)
        {
            if (i == q[j])
                w = 0;
            if (i > q[j])
                q[j] += (p[j] << 1);
        }
        if (w)
            p.push_back(i);
    }
    return p;
}
