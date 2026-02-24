#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
vector<vector<double> > mul(vector<vector<double> > v, vector<vector<double> > A)
{
    vector<vector<double> > ans(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        ans[i].resize(A[0].size());
        for (int k = 0; k < A[0].size(); k++)
            ans[i][k] = 0;
        for (int j = 0; j < A.size(); j++)
        {
            for (int k = 0; k < A[0].size(); k++)
                ans[i][k] += v[i][j] * A[j][k];
        }
    }
    return ans;
}
void print(vector<double> v)
{
    cout << v[0] << ' ' << v[1] << '\n';
}
void tr(vector<vector<double> >& v, vector<vector<double> > A)
{
    for (auto& h : v)
    {
        h = mul({h}, A)[0];
        print(h);
    }
    cout << '\n';
}
int main()
{
    ifstream in("square.obj");
    string s;
    vector<vector<double> > v;
    double a, b;
    while (in >> s)
    {
        if (s == "v")
        {
            v.push_back({0, 0, 1});
            in >> v.back()[0] >> v.back()[1] >> a;
        }
    }
    vector<vector<double> > A, B, C, D, E;
    A = {{1, 0, 0}, {0, 1, 0}, {2, 0, 1}};
    tr(v, A);
    a = b = 0;
    for (auto h : v)
    {
        a += h[0];
        b += h[1];
    }
    a /= v.size();
    b /= v.size();
    D = {{1, 0, 0}, {0, 1, 0}, {a, b, 1}};
    E = {{1, 0, 0}, {0, 1, 0}, {-a, -b, 1}};
    B = {{sqrt(0.5), sqrt(0.5), 0}, {-sqrt(0.5), sqrt(0.5), 0}, {0, 0, 1}};
    tr(v, mul(E, mul(B, D)));
    C = {{2, 0, 0}, {0, 2, 0}, {0, 0, 1}};
    tr(v, mul(E, mul(C, D)));
}
