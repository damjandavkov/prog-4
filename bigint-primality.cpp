#include <iostream>
#include <vector>
#include <string>
using namespace std;
class big
{
public:
    vector<int> n;
    big(int a)
    {
        while (a > 0)
        {
            n.push_back(a & 1);
            a >>= 1;
        }
    }
    big(string a);
    big()
    {

    }
    void cl()
    {
        while (!n.empty() && !n.back())
            n.pop_back();
    }
};
ostream& operator <<(ostream& os, big a)
{
    for (int i = (int)a.n.size() - 1; i >= 0; i--)
        os << a.n[i];
    return os;
}
void operator *=(big& a, big b)
{
    big c;
    c.n.resize(a.n.size() + b.n.size());
    for (int i = 0; i < a.n.size(); i++)
    {
        for (int j = 0; j < b.n.size(); j++)
            c.n[i + j] += a.n[i] * b.n[j];
    }
    for (int i = 0; i + 1 < c.n.size(); i++)
    {
        c.n[i + 1] += c.n[i] >> 1;
        c.n[i] &= 1;
    }
    c.cl();
    a.n = c.n;
}
bool operator <(big a, big b)
{
    if (a.n.size() != b.n.size())
        return a.n.size() < b.n.size();
    for (int i = (int)a.n.size() - 1; i >= 0; i--)
    {
        if (a.n[i] != b.n[i])
            return a.n[i] < b.n[i];
    }
    return 0;
}
bool operator -=(big& a, big b)
{
    if (a < b)
        return 0;
    for (int i = 0; i < a.n.size(); i++)
    {
        if (i < b.n.size())
            a.n[i] -= b.n[i];
        if (a.n[i] < 0)
        {
            a.n[i] += 2;
            a.n[i + 1]--;
        }
    }
    a.cl();
    return 1;
}
big operator <<(big a, int n)
{
    big c;
    while (n--)
        c.n.push_back(0);
    for (auto h : a.n)
        c.n.push_back(h);
    return c;
}
void operator %=(big& a, big b)
{
    for (int i = (int)a.n.size() - b.n.size(); i >= 0; i--)
    {
        big c = (b << i);
        while (a -= c)
            continue;
    }
    a.cl();
}
bool operator ==(big a, big b)
{
    return !((a < b) || (b < a));
}
big pow(big b, big e, big m, int t)
{
    big c(1);
    for (int i = t; i < e.n.size(); i++)
    {
        if (e.n[i])
        {
            c *= b;
            c %= m;
        }
        b *= b;
        b %= m;
    }
    return c;
}
bool fermat(big p, int k)
{
    big d(1), q(p);
    if (q == d)
        return 0;
    q -= d;
    for (int i = 0; i < k; i++)
    {
        while (1)
        {
            big c(rand() + 2);
            c %= p;
            if (c.n.empty())
                continue;
            if (!(pow(c, q, p, 0) == d))
                return 0;
            break;
        }
    }
    return 1;
}
bool miller_rabin(big p, int k)
{
    big d(1), q(p);
    if (q == d)
        return 0;
    q -= d;
    if (q == d)
        return 1;
    int t;
    for (t = 0; t < q.n.size(); t++)
    {
        if (q.n[t])
            break;
    }
    if (!t)
        return 0;
    for (int i = 0; i < k; i++)
    {
        while (1)
        {
            big c(rand() + 2);
            c %= p;
            if (c.n.empty())
                continue;
            big u = pow(c, q, p, t);
            if (u == d)
                break;
            int j;
            for (j = 0; j < t; j++)
            {
                if (u == q)
                    break;
                u *= u;
                u %= p;
            }
            if (j == t)
                return 0;
            break;
        }
    }
    return 1;
}
big::big(string a)
{
    big c(0), d(10);
    for (auto h : a)
    {
        c *= d;
        if (c.n.empty())
            c.n.push_back(0);
        c.n[0] += h - '0';
        for (int i = 0; i + 1 < c.n.size(); i++)
        {
            c.n[i + 1] += c.n[i] >> 1;
            c.n[i] &= 1;
        }
        while (c.n.back())
        {
            c.n.back() &= 1;
            c.n.push_back(c.n.back() >> 1);
        }
    }
    c.cl();
    n = c.n;
}
