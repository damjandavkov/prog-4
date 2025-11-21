#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
void push(int i, int j, vector<vector<int> >& f, vector<int>& ex, queue<int>& q)
{
    int fl = min(ex[i], f[i][j]);
    if (!fl)
        return;
    f[i][j] -= fl;
    f[j][i] += fl;
    ex[i] -= fl;
    if (!ex[j])
        q.push(j);
    ex[j] += fl;
}
void rlb(int n, int i, vector<vector<int> >& f, vector<int>& h)
{
    int mn = 1073741823;
    for (int j = 0; j < n; j++)
    {
        if (f[i][j])
            mn = min(mn, h[j]);
    }
    if (mn < 1073741823)
        h[i] = mn + 1;
}
void dpu(int n, int i, vector<vector<int> >& f, vector<int>& h, vector<int>& ex, vector<int>& la, queue<int>& q)
{
    while (ex[i])
    {
        if (la[i] < n)
        {
            if (f[i][la[i]] && h[i] > h[la[i]])
                push(i, la[i], f, ex, q);
            la[i]++;
        }
        else
        {
            rlb(n, i, f, h);
            la[i] = 0;
        }
    }
}
int flow(int n, vector<vector<int> >& c)
{
    vector<vector<int> > f = c;
    vector<int> h(n, 0), ex(n, 0), la(n, 0);
    h[0] = n;
    ex[0] = 1073741823;
    queue<int> q;
    for (int i = 1; i < n; i++)
        push(0, i, f, ex, q);
    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        if (i && i != n - 1)
            dpu(n, i, f, h, ex, la, q);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += c[i][n - 1] - f[i][n - 1];
    return ans;
}
int main()
{
    vector<string> files = {"push-relabel-tests/test-0-random.in", "push-relabel-tests/test-1-corner-0.in", "push-relabel-tests/test-2-corner-1.in", "push-relabel-tests/test-3-special-0.in", "push-relabel-tests/test-4-special-1.in", "push-relabel-tests/test-5-special-2.in", "push-relabel-tests/test-6-demo.in", "push-relabel-tests/test-7-dinic.in", "push-relabel-tests/test-8-matching.in", "push-relabel-tests/test-9-waif.in", "push-relabel-tests/test-10-reduction-0.in", "push-relabel-tests/test-11-reduction-1.in", "push-relabel-tests/test-12-reduction-2.in", "push-relabel-tests/test-13-mcmf-0.in", "push-relabel-tests/test-14-mcmf-1.in"};
    ofstream out("push-relabel-tests/tests.out");
    for (auto s : files)
    {
        ifstream in(s);
        int n, m;
        in >> n >> m;
        vector<vector<int> > c(n, vector<int>(n, 0));
        while (m--)
        {
            int a, b, d;
            in >> a >> b >> d;
            c[a][b] = d;
        }
        out << flow(n, c) << '\n';
    }
}
