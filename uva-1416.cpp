#include <iostream>
#include <vector>
using namespace std;
vector<vector<long long> > fw(int n, vector<vector<long long> > ma)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                ma[i][j] = min(ma[i][j], ma[i][k] + ma[k][j]);
        }
    }
    return ma;
}
int main()
{
    int INF = 268435456, n, m, L;
    cin >> n >> m >> L;
    vector<vector<long long> > ma(n, vector<long long>(n, INF)), ma2, ed(m);
    for (int i = 0; i < n; i++)
        ma[i][i] = 0;
    for (int i = 0; i < m; i++)
    {
        ed[i].resize(3);
        cin >> ed[i][0] >> ed[i][1] >> ed[i][2];
        int a = ed[i][0] - 1, b = ed[i][1] - 1;
        ma[a][b] = ma[b][a] = ed[i][2];
    }
    long long C, c, mc;
    ma2 = fw(n, ma);
    c = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ma2[i][j] == INF)
                c += L;
            else
                c += ma2[i][j];
        }
    }
    mc = C = c;
    for (int k = 0; k < m; k++)
    {
        int a = ed[k][0] - 1, b = ed[k][1] - 1;
        ma[a][b] = ma[b][a] = INF;
        ma2 = fw(n, ma);
        ma[a][b] = ma[b][a] = ed[k][2];
        c = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (ma2[i][j] == INF)
                    c += L;
                else
                    c += ma2[i][j];
            }
        }
        mc = max(mc, c);
    }
    cout << C << ' ' << mc;
}
