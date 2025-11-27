#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
int main()
{
    string s;
    vector<bool> w(26, 0);
    cin >> s;
    int n = s.size(), k, ans = 0;
    for (int i = 0; i < 26; i++)
    {
        char c;
        cin >> c;
        if (c == '1')
            w[i] = 1;
    }
    cin >> k;
    vector<long long> hs(n + 1), hs2(n + 1), po(n + 1), po2(n + 1);
    vector<int> bd(n + 1);
    bd[0] = 0;
    for (int i = 0; i < n; i++)
    {
        bd[i + 1] = bd[i];
        if (!w[s[i] - 'a'])
            bd[i + 1]++;
    }
    long long X = 843899, R = 1000000007, R2 = 1000000009;
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
    for (int m = 1; m <= n; m++)
    {
        set<pair<long long, long long> > se;
        for (int i = 0; i <= n - m; i++)
        {
            if (bd[i + m] - bd[i] > k)
                continue;
            se.insert({(hs[i + m] - hs[i] + R) * po[n - i] % R, (hs2[i + m] - hs2[i] + R2) * po2[n - i] % R2});
        }
        ans += se.size();
    }
    cout << ans;
}
