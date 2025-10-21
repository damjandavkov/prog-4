#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dfs(int n, int fr, int fl, vector<vector<int> > & nv, vector<int>& pt, vector<vector<int> >& c)
{
    if (!fl)
        return 0;
    if (fr == n - 1)
        return fl;
    for (; pt[fr] < nv[fr].size(); pt[fr]++)
    {
        int to = nv[fr][pt[fr]];
        int nfl = dfs(n, to, min(fl, c[fr][to]), nv, pt, c);
        if (!nfl)
            continue;
        c[fr][to] -= nfl;
        c[to][fr] += nfl;
        return nfl;
    }
    return 0;
}
int flow(int n, vector<vector<int> > c)
{
    vector<vector<int> > C = c;
    const int INF = 1073741823;
    int ans = 0;
    while (1)
    {
        vector<vector<int> > v(n), nv(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (c[i][j])
                {
                    v[i].push_back(j);
                    v[j].push_back(i);
                }
            }
        }
        vector<int> di(n, INF);
        di[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int fr = q.front();
            q.pop();
            for (auto to : v[fr])
            {
                if (c[fr][to] && di[to] == INF)
                {
                    di[to] = di[fr] + 1;
                    q.push(to);
                    nv[fr].push_back(to);
                }
            }
        }
        if (di[n - 1] == INF)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    cout << max(0, C[i][j] - c[i][j]) << ' ';
                cout << '\n';
            }
            return ans;
        }
        vector<int> pt(n);
        for (int i = 0; i < n; i++)
            pt[i] = 0;
        while (1)
        {
            int fl = dfs(n, 0, INF, nv, pt, c);
            if (fl)
                ans += fl;
            else
                break;
        }
    }
}
