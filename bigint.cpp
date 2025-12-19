#include <iostream>
#include <vector>
#include <string>
using namespace std;
class big
{
public:
    bool sgn;
    vector<int> num;
    big()
    {
        sgn = 0;
        num.clear();
    }
    big(string s)
    {
        sgn = 0;
        num.clear();
        if (s.empty())
            return;
        if (s[0] == '-')
        {
            sgn = 1;
            bool w = 1;
            for (int i = s.size() - 1; i; i--)
            {
                if (w)
                {
                    if (s[i] == '0')
                        num.push_back(0);
                    else
                    {
                        w = 0;
                        num.push_back(58 - s[i]);
                    }
                }
                else
                    num.push_back(57 - s[i]);
            }
            while (num.back() == 9)
                num.pop_back();
            if (w)
            {
                sgn = 0;
                num.clear();
            }
        }
        else
        {
            sgn = 0;
            for (int i = s.size() - 1; i >= 0; i--)
                num.push_back(s[i] - 48);
            while (!num.back())
                num.pop_back();
        }
    }
    big(const big& o)
    {
        sgn = o.sgn;
        num = o.num;
    }
    big operator =(const big& o)
    {
        sgn = o.sgn;
        num = o.num;
        return *this;
    }
    bool operator ==(const big& o) const
    {
        if (sgn != o.sgn)
            return 0;
        if (num.size() != o.num.size())
            return 0;
        for (int i = num.size() - 1; i >= 0; i--)
        {
            if (num[i] != o.num[i])
                return 0;
        }
        return 1;
    }
    bool operator <(const big& o) const
    {
        if (sgn && !o.sgn)
            return 1;
        if (!sgn && o.sgn)
            return 0;
        if (num.size() < o.num.size())
            return !sgn;
        if (o.num.size() < num.size())
            return sgn;
        for (int i = num.size() - 1; i >= 0; i--)
        {
            if (num[i] < o.num[i])
                return 1;
            if (o.num[i] < num[i])
                return 0;
        }
        return 0;
    }
};
ostream& operator <<(ostream& os, const big& o)
{
    if (o.sgn)
    {
        os << '-';
        int j = 0;
        while (j < o.num.size() && !o.num[j])
            j++;
        if (j == o.num.size())
            os << 1;
        else
        {
            for (int i = o.num.size() - 1; i > j; i--)
                os << 9 - o.num[i];
            os << 10 - o.num[j];
        }
        while (j--)
            os << 0;
    }
    else
    {
        if (o.num.empty())
            os << 0;
        else
        {
            for (int i = o.num.size() - 1; i >= 0; i--)
                os << o.num[i];
        }
    }
    return os;
}
big operator +(const big& a, const big& b)
{
    big c;
    c.num.resize(max(a.num.size(), b.num.size()) + 1);
    for (int i = 0; i < c.num.size(); i++)
        c.num[i] = 0;
    for (int i = 0; i < c.num.size(); i++)
    {
        if (i < a.num.size())
            c.num[i] += a.num[i];
        else if (a.sgn)
            c.num[i] += 9;
        if (i < b.num.size())
            c.num[i] += b.num[i];
        else if (b.sgn)
            c.num[i] += 9;
        cout << i << ' ' << c.num[i] << '\n';
        if (i + 1 < c.num.size())
        {
            c.num[i + 1] += c.num[i] / 10;
            c.num[i] %= 10;
        }
        else
        {
            int s = 0;
            if (a.sgn)
                s += 10;
            if (b.sgn)
                s += 10;
            if (c.num[i] < s)
                c.sgn = 1;
            else
                c.sgn = 0;
            c.num[i] %= 10;
        }
    }
    if (c.sgn)
    {
        while (c.num.back() == 9)
            c.num.pop_back();
    }
    else
    {
        while (!c.num.back())
            c.num.pop_back();
    }
    return c;
}
big operator -(const big& a, const big& b)
{
    big c;
    c.num.resize(max(a.num.size(), b.num.size()) + 1);
    for (int i = 0; i < c.num.size(); i++)
        c.num[i] = 0;
    for (int i = 0; i < c.num.size(); i++)
    {
        if (i < a.num.size())
            c.num[i] += a.num[i];
        else if (a.sgn)
            c.num[i] += 9;
        if (i < b.num.size())
            c.num[i] += 9 - b.num[i];
        else if (!b.sgn)
            c.num[i] += 9;
        if (!i)
            c.num[i]++;
        if (i + 1 < c.num.size())
        {
            c.num[i + 1] += c.num[i] / 10;
            c.num[i] %= 10;
        }
        else
        {
            int s = 0;
            if (a.sgn)
                s += 10;
            if (!b.sgn)
                s += 10;
            if (c.num[i] < s)
                c.sgn = 1;
            else
                c.sgn = 0;
            c.num[i] %= 10;
        }
    }
    if (c.sgn)
    {
        while (c.num.back() == 9)
            c.num.pop_back();
    }
    else
    {
        while (!c.num.back())
            c.num.pop_back();
    }
    return c;
}
big operator *(const big& a, const big& b)
{
    if (!a.sgn && a.num.empty())
        return a;
    if (!b.sgn && b.num.empty())
        return b;
    big c;
    c.sgn = a.sgn ^ b.sgn;
    c.num.resize(a.num.size() + b.num.size() + 1);
    for (int i = 0; i < c.num.size(); i++)
        c.num[i] = 0;
    for (int i = 0; i < c.num.size(); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            int da = 0, db = 0;
            if (j < a.num.size())
                da = a.num[j];
            else if (a.sgn)
                da = 9;
            if (i - j < b.num.size())
                db = b.num[i - j];
            else if (b.sgn)
                db = 9;
            c.num[i] += da * db;
        }
        if (i + 1 < c.num.size())
            c.num[i + 1] += c.num[i] / 10;
        c.num[i] %= 10;
    }
    if (c.sgn)
    {
        while (c.num.back() == 9)
            c.num.pop_back();
    }
    else
    {
        while (!c.num.back())
            c.num.pop_back();
    }
    return c;
}
