#include <vector>
#include <string>
#include <set>
using namespace std;
class Solution
{
public:
    string longestDupSubstring(string s)
    {
        int n = s.size();
        long long X = 293832, R = 1000000007, R2 = 1000000009;
        vector<long long> po(n + 1), hs(n + 1), po2(n + 1), hs2(n + 1);
        po[0] = 1;
        for (int i = 0; i < n; i++)
            po[i + 1] = po[i] * X % R;
        po2[0] = 1;
        for (int i = 0; i < n; i++)
            po2[i + 1] = po2[i] * X % R2;
        hs[0] = 0;
        for (int i = 0; i < n; i++)
            hs[i + 1] = (hs[i] + (s[i] - 'a') * po[i]) % R;
        hs2[0] = 0;
        for (int i = 0; i < n; i++)
            hs2[i + 1] = (hs2[i] + (s[i] - 'a') * po2[i]) % R2;
        int hi = n + 1, lo = 0;
        while (hi - lo > 1)
        {
            int m = (hi + lo) / 2;
            set<pair<long long, long long> > se;
            for (int i = 0; i <= n - m; i++)
                se.insert({(hs[i + m] - hs[i] + R) * po[n - i] % R, (hs2[i + m] - hs2[i] + R2) * po2[n - i] % R2});
            if (se.size() <= n - m)
                lo = m;
            else
                hi = m;
        }
        if (!lo)
            return "";
        else
        {
            set<pair<long long, long long> > se;
            for (int i = 0; i <= n - lo; i++)
            {
                pair<int, int> p = {(hs[i + lo] - hs[i] + R) * po[n - i] % R, (hs2[i + lo] - hs2[i] + R2) * po2[n - i] % R2};
                if (se.find(p) != se.end())
                    return s.substr(i, lo);
                se.insert(p);
            }
        }
    }
};
