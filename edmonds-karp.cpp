#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int flow(int n, vector<vector<int> > c)
{
    vector<vector<int> > v(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (c[i][j] || c[j][i])
                v[i].push_back(j);
        }
    }
    const int INF = 1073741823;
    int ans = 0;
    while (1)
    {
        vector<int> pa(n, -1);
        queue<pair<int, int> > q;
        pa[0] = 0;
        q.push({0, INF});
        int an = -1;
        while (!q.empty())
        {
            int fr = q.front().first, fl = q.front().second;
            q.pop();
            for (auto to : v[fr])
            {
                if (pa[to] == -1 && c[fr][to])
                {
                    pa[to] = fr;
                    int t = min(fl, c[fr][to]);
                    if (to == n - 1)
                    {
                        an = t;
                        break;
                    }
                    q.push({to, t});
                }
            }
            if (an != -1)
                break;
        }
        if (an == -1)
            break;
        ans += an;
        vector<int> o;
        for (int i = n - 1; i; i = pa[i])
        {
            c[pa[i]][i] -= an;
            c[i][pa[i]] += an;
            o.push_back(i);
        }
        o.push_back(0);
        cout << an << ' ';
        for (int i = o.size() - 1; i >= 0; i--)
            cout << ' ' << o[i];
        cout << '\n';
    }
    return ans;
}
