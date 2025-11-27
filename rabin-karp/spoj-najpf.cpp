#include <iostream>
#include <string>
#include <vector>
using namespace std;
void solve()
{
    string a;
    string b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    long long X = 982392, R = 1000000007;
    vector<long long> po(max(n, m) + 1), hs(n + 1);
    po[0] = 1;
    for (int i = 0; i < max(n, m); i++)
        po[i + 1] = po[i] * X % R;
    hs[0] = 0;
    for (int i = 0; i < n; i++)
        hs[i + 1] = (hs[i] + (a[i] - 'a') * po[i]) % R;
    long long hsb = 0;
    for (int i = 0; i < m; i++)
        hsb = (hsb + (b[i] - 'a') * po[i]) % R;
    vector<int> oc;
    for (int i = 0; i <= n - m; i++)
    {
        if (hs[i + m] == (hsb * po[i] + hs[i]) % R)
            oc.push_back(i);
    }
    if (oc.empty())
        cout << "Not Found\n";
    else
    {
        cout << oc.size() << '\n';
        for (auto h : oc)
            cout << h + 1 << ' ';
        cout << '\n';
    }
    cout << '\n';
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}
