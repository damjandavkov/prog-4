#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> ans(n, 0);
    long long X = 349348, R = 1000000007;
    vector<long long> po(n + 1), hfo(n + 1), hba(n + 1);
    po[0] = 1;
    for (int i = 0; i < n; i++)
        po[i + 1] = po[i] * X % R;
    hfo[0] = 0;
    for (int i = 0; i < n; i++)
        hfo[i + 1] = (hfo[i] + (s[i] - 'a') * po[i]) % R;
    hba[0] = 0;
    for (int i = 0; i < n; i++)
        hba[i + 1] = (hba[i] + (s[i] - 'a') * po[n - i]) % R;
    vector<vector<int> > pal(n);
    for (int m = 0; m < n; m++)
    {
        pal[m].resize(n - m);
        for (int i = 0; i < n - m; i++)
        {
            if ((hfo[i + m + 1] - hfo[i] + R) * po[n - m - i] % R != (hba[i + m + 1] - hba[i] + R) * po[i] % R)
                pal[m][i] = 0;
            else if (!m)
                pal[m][i] = 1;
            else
                pal[m][i] = pal[(m - 1) / 2][i] + 1;
            for (int j = 0; j < pal[m][i]; j++)
                ans[j]++;
        }
    }
    for (auto h : ans)
        cout << h << ' ';
}
