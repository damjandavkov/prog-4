#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
vector<int> bf(int n, vector<vector<int> >& ed)
{
    const int INF = 2147483647;
    vector<int> di(n, INF);
    di[0] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (auto e : ed)
        {
            if (di[e[0]] != INF && di[e[1]] > di[e[0]] + e[2])
                di[e[1]] = di[e[0]] + e[2];
        }
    }
    for (auto e : ed)
    {
        if (di[e[0]] != INF && di[e[1]] > di[e[0]] + e[2])
            return {};
    }
    return di;
}
bool con(int n, vector<vector<int> >& ed)
{
    vector<bool> vi(n, 0);
    vi[0] = 1;
    vector<vector<int> > v(n);
    for (auto e : ed)
        v[e[0]].push_back(e[1]);
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        for (auto g : v[i])
        {
            if (!vi[g])
            {
                vi[g] = 1;
                q.push(g);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (!vi[i])
            return 0;
    }
    return 1;
}
int main()
{
    int n = 50, m = 234;
    for (int i = 0; i < 10; i++)
    {
        vector<vector<int> > ed(m);
        for (int j = 0; j < m; j++)
            ed[j] = {rand() % n, rand() % n, rand() % 50 - 3};
        if (!con(n, ed))
            i--;
        else
        {
            string name = "test0.txt";
            name[4] = '0' + i;
            ofstream out(name);
            out << n << ' ' << m << '\n';
            for (auto e : ed)
                out << e[0] << ' ' << e[1] << ' ' << e[2] << '\n';
            vector<int> ans = bf(n, ed);
            if (ans.empty())
                out << "NEGATIVE CYCLE";
            else
            {
                for (auto g : ans)
                    out << g << ' ';
            }
        }
    }
}
