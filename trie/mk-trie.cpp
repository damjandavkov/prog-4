#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <map>
using namespace std;
struct trie
{
    map<string, trie*> next;
    bool word;
    trie()
    {
        next.clear();
        word = 0;
    }
    void insert(string s)
    {
        trie* t = this;
        for (int i = 0; i < s.size(); i += 2)
        {
            string c = s.substr(i, 2);
            if (!t->next[c])
                t->next[c] = new trie();
            t = t->next[c];
        }
        t->word = 1;
    }
    void print(string s)
    {
        cout << word;
        for (int i = 0; i < s.size(); i += 2)
            cout << ' ';
        cout << s << '\n';
        for (auto [i, j] : next)
            j->print(s + i);
    }
};
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    ifstream in("MK-dict.txt");
    trie* root = new trie();
    string s;
    while (getline(in, s))
        root->insert(s);
    root->print("");
}
