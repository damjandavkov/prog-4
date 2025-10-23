#include <iostream>
#include <vector>
#include <queue>
using namespace std;
long long flow(int n, vector<vector<int> > c)
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
    long long ans = 0;
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
        for (int i = n - 1; i; i = pa[i])
        {
            c[pa[i]][i] -= an;
            c[i][pa[i]] += an;
        }
    }
    return ans;
}
int main()
{
    int INF = 1073741824, n, m;
    cin >> n >> m;
    vector<vector<int> > c(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        int a, b, d;
        cin >> a >> b >> d;
        a--;
        b--;
        c[a][b] = c[b][a] = d;
    }
    long long fl = flow(n, c);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (c[i][j])
            {
                int d = c[i][j];
                c[i][j] = 0;
                fl = min(fl, flow(n, c));
                c[i][j] = d;
            }
        }
    }
    cout << fl;
}
