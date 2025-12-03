#include <iostream>
#include <string>
using namespace std;
class german
{
    unsigned int sz;
    char a[12];
    char* pt() const
    {
        if (sz <= 12)
            return 0;
        unsigned long long p = 0;
        for (int i = 4; i < 12; i++)
            p += (unsigned long long)(unsigned char)a[i] << (11 - i << 3);
        return (char*)p;
    }
public:
    german(const string& s)
    {
        sz = s.size();
        if (sz > 12)
        {
            for (int i = 0; i < 4; i++)
                a[i] = s[i];
            char* b = new char[sz];
            for (int i = 0; i < sz; i++)
                b[i] = s[i];
            for (int i = 4; i < 12; i++)
                a[i] = (unsigned long long)b >> (11 - i << 3) & 255;
        }
        else
        {
            for (int i = 0; i < sz; i++)
                a[i] = s[i];
            for (int i = sz; i < 12; i++)
                a[i] = 0;
        }
    }
    german(const german& o)
    {
        sz = o.sz;
        for (int i = 0; i < 12; i++)
            a[i] = o.a[i];
    }
    operator =(const german& o)
    {
        sz = o.sz;
        for (int i = 0; i < 12; i++)
            a[i] = o.a[i];
    }
    unsigned long long size() const
    {
        return sz;
    }
    string toString() const
    {
        string an;
        an.resize(sz);
        if (sz > 12)
        {
            char* p = pt();
            for (int i = 0; i < sz; i++)
                an[i] = p[i];
        }
        else
        {
            for (int i = 0; i < sz; i++)
                an[i] = a[i];
        }
        return an;
    }
    char& at(unsigned int i)
    {
        if (i >= sz)
            return a[0];
        if (i < 4)
            return a[i];
        if (sz > 12)
            return pt()[i];
        return a[i];
    }
    char& operator [](unsigned int i)
    {
        if (i >= sz)
            return a[0];
        if (i < 4)
            return a[i];
        if (sz > 12)
            return pt()[i];
        return a[i];
    }
    bool operator ==(const german& o) const
    {
        if (sz > 12)
        {
            for (int i = 0; i < 4; i++)
            {
                if (a[i] != o.a[i])
                    return 0;
            }
            char* p = pt();
            char* op = o.pt();
            for (int i = 4; i < sz; i++)
            {
                if (p[i] != op[i])
                    return 0;
            }
        }
        else
        {
            for (int i = 0; i < sz; i++)
            {
                if (a[i] != o.a[i])
                    return 0;
            }
        }
        return 1;
    }
    bool operator <(const german& o) const
    {
        if (sz > 12)
        {
            for (int i = 0; i < 4; i++)
            {
                if (a[i] < o.a[i])
                    return 1;
                if (a[i] > o.a[i])
                    return 0;
            }
            char* p = pt();
            char* op = o.pt();
            for (int i = 4; i < sz; i++)
            {
                if (p[i] < op[i])
                    return 1;
                if (p[i] > op[i])
                    return 0;
            }
        }
        else
        {
            for (int i = 0; i < sz; i++)
            {
                if (a[i] < o.a[i])
                    return 1;
                if (a[i] > o.a[i])
                    return 0;
            }
        }
        return 0;
    }
    german operator +(const german& o) const
    {
        return german(toString() + o.toString());
    }
};
ostream& operator <<(ostream& out, const german& s)
{
    out << s.toString();
    return out;
}
