#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
vector<double> mul(vector<double> v, vector<vector<double> > A)
{
    vector<double> ans(v.size());
    for (int i = 0; i < v.size(); i++)
        ans[i] = 0;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
            ans[j] += v[i] * A[i][j];
    }
    return ans;
}
void tr(vector<double>& v, double tx, double ty, double tz)
{
    v = mul(v, {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {tx, ty, tz, 1}});
}
void rot(vector<double>& v, double ag, char ax)
{
    double cs = cos(ag * M_PI / 180), sn = sin(ag * M_PI / 180);
    if (ax == 'x')
        v = mul(v, {{1, 0, 0, 0}, {0, cs, sn, 0}, {0, -sn, cs, 0}, {0, 0, 0, 1}});
    if (ax == 'y')
        v = mul(v, {{cs, 0, -sn, 0}, {0, 1, 0, 0}, {sn, 0, cs, 0}, {0, 0, 0, 1}});
    if (ax == 'z')
        v = mul(v, {{cs, sn, 0, 0}, {-sn, cs, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}
void sc(vector<double>& v, double sx, double sy, double sz)
{
    v = mul(v, {{sx, 0, 0, 0}, {0, sy, 0, 0}, {0, 0, sz, 0}, {0, 0, 0, 1}});
}
int main()
{
    ifstream in("monkey.obj");
    string s;
    vector<vector<double> > v;
    double a, b, c;
    while (in >> s)
    {
        if (s == "v")
        {
            v.push_back({0, 0, 0, 1});
            in >> v.back()[0] >> v.back()[1] >> v.back()[2];
        }
    }
    a = b = c = 0;
    for (auto h : v)
    {
        a += h[0];
        b += h[1];
        c += h[2];
    }
    a /= v.size();
    b /= v.size();
    c /= v.size();
    ofstream out("newmonkey.obj");
    for (auto& h : v)
    {
        tr(h, -a, -b, -c);
        rot(h, 45, 'x');
        rot(h, 27, 'y');
        rot(h, 10, 'z');
        sc(h, 1.5, -1, 1);
        tr(h, a, b, c);
        out << 'v' << ' ' << h[0] << ' ' << h[1] << ' ' << h[2] << '\n';
    }
}
