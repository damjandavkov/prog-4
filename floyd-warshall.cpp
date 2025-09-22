#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> > fwm(int n, vector<vector<int> >& ma)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                ma[i][j] = min(ma[i][j], ma[i][k] + ma[k][j]);
            if (ma[i][i] < 0)
                return {};
        }
    }
    return ma;
}
vector<vector<int> > fwe(int n, vector<vector<int> >& ed)
{
    int INF = 268435456;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool is = 0;
            for (auto& e : ed)
            {
                if (e[0] == i && e[1] == j)
                {
                    is = 1;
                    break;
                }
            }
            if (!is)
            {
                if (i == j)
                    ed.push_back({i, j, 0});
                else
                    ed.push_back({i, j, INF});
            }
        }
    }
    vector<int> to(n), fro(n);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
            to[i] = fro[i] = INF;
        for (auto& e : ed)
        {
            if (e[1] == k)
                fro[e[0]] = e[2];
            if (e[0] == k)
                to[e[1]] = e[2];
        }
        for (auto& e : ed)
        {
            e[2] = min(e[2], fro[e[0]] + to[e[1]]);
            if (e[0] == e[1] && e[2] < 0)
                return {};
        }
    }
    return ed;
}
/*int main()
{
    int INF = 268435456, n = 4;
    vector<vector<int> > matrix = {{0, INF, 1, -2}, {9, 0, INF, INF}, {INF, -1, 0, 7}, {3, INF, 2, 0}};
    vector<vector<int> > edges = {{0, 2, 1}, {0, 3, -2}, {2, 1, -1}, {3, 2, 2}, {3, 0, 3}, {1, 0, 9}, {2, 3, 7}};
    vector<vector<int> > ansM = fwm(n, matrix);
    vector<vector<int> > ansE = fwe(n, edges);
    if (ansM.empty())
        cout << "NEGATIVE CYCLE\n";
    for (auto& a : ansM)
    {
        for (auto& b : a)
            cout << b << ' ';
        cout << '\n';
    }
    cout << '\n';
    if (ansE.empty())
        cout << "NEGATIVE CYCLE\n";
    for (auto& a : ansE)
    {
        for (auto& b : a)
            cout << b << ' ';
        cout << '\n';
    }
}*/
