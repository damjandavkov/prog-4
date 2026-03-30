#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    ifstream in("in.obj");
    ofstream out("out.obj");
    char ch;
    vector<vector<int> > po = {{-99, -99}, {99, -99}, {0, 99}}, del = {{0, 1, 2}};
    while (in >> ch)
    {
        int a, b;
        in >> a >> b;
        out << 'v' << ' ' << a << ' ' << b << '\n';
        po.push_back({a, b});
        vector<vector<int> > ed, ndel;
        for (auto& tr : del)
        {
            int ax = po[tr[0]][0] - a, ay = po[tr[0]][1] - b, bx = po[tr[1]][0] - a, by = po[tr[1]][1] - b, cx = po[tr[2]][0] - a, cy = po[tr[2]][1] - b;
            int s = ax * by + bx * cy + cx * ay - ay * bx - by * cx - cy * ax;
            int t = (ax * by - ay * bx) * (cx * cx + cy * cy) + (bx * cy - by * cx) * (ax * ax + ay * ay) + (cx * ay - cy * ax) * (bx * bx + by * by);
            if ((s > 0 && t > 0) || (s < 0 && t < 0))
            {
                ed.push_back({tr[0], tr[1]});
                ed.push_back({tr[0], tr[2]});
                ed.push_back({tr[1], tr[2]});
            }
            else
                ndel.push_back(tr);
        }
        sort(ed.begin(), ed.end());
        for (int i = 0; i < ed.size(); i++)
        {
            if ((i + 1 == ed.size() || ed[i][0] != ed[i + 1][0] || ed[i][1] != ed[i + 1][1]) && (!i || ed[i][0] != ed[i - 1][0] || ed[i][1] != ed[i - 1][1]))
                ndel.push_back({ed[i][0], ed[i][1], po.size() - 1});
        }
        del = ndel;
    }
    for (auto& tr : del)
    {
        if (tr[0] > 2)
            out << 'f' << ' ' << tr[0] - 2 << ' ' << tr[1] - 2 << ' ' << tr[2] - 2 << '\n';
    }
}
