#include <fstream>
#include <iostream>
#include <string>
using namespace std;
struct trie
{
    trie* next[26];
    bool word;
    string pref;
    trie()
    {
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
        word = 0;
        pref.clear();
    }
    void insert(string s)
    {
        trie* t = this;
        for (auto& h : s)
        {
            int c = h - 'a';
            if (!t->next[c])
                t->next[c] = new trie();
            t = t->next[c];
        }
        t->word = 1;
    }
    void print(string s, int d)
    {
        s += pref;
        cout << word;
        for (int i = 0; i < d; i++)
            cout << ' ';
        cout << s << '\n';
        for (int i = 0; i < 26; i++)
        {
            if (!next[i])
                continue;
            next[i]->print(s + char('a' + i), d + 1);
        }
    }
    void patricia()
    {
        int z = 0, c;
        for (int i = 0; i < 26; i++)
        {
            if (!next[i])
                continue;
            z++;
            next[i]->patricia();
            c = i;
        }
        if (z != 1 || word)
            return;
        trie* ch = next[c];
        for (int i = 0; i < 26; i++)
            next[i] = ch->next[i];
        pref = char('a' + c) + ch->pref;
        word = ch->word;
    }
};
int main()
{
    ifstream in("wiki-100k.txt");
    string s;
    trie* root = new trie();
    while (getline(in, s))
    {
        for (auto& h : s)
        {
            if (h >= 'A' && h <= 'Z')
                h += 32;
            if (h < 'a' || h > 'z')
            {
                s.clear();
                break;
            }
        }
        if (s.empty())
            continue;
        root->insert(s);
    }
    root->print("", 0);
    root->patricia();
    cout << '\n';
    root->print("", 0);
}
