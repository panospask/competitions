#include <bits/stdc++.h>

using namespace std;

int n;
queue<char> ans;

struct Trie {
    int maxlength = 0;
    int size = 0;
    char maxkid = '\0';
    bool isword = false;
    map<char, Trie> kids;

    void insert(const string& word, int pos)
    {
        size++;
        if
            (pos == word.size()) isword = true;
        else
            kids[word[pos]].insert(word, pos + 1);

        if (word.size() - pos + 1 > maxlength) {
            maxlength = word.size() - pos + 1;
            maxkid = word[pos];
        }
    }


    void calculate_answer(bool leaveit)
    {
        if (isword)
            ans.push('P');
        for (auto kid : kids)
            if (kid.first != maxkid && kid.second.size) {
                ans.push(kid.first);
                kid.second.calculate_answer(false);
                ans.push('-');
            }
        if (maxkid != '\0') {
            ans.push(maxkid);
            kids[maxkid].calculate_answer(leaveit);
            if (!leaveit)
                ans.push('-');
        }
    }
};

Trie t;
int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        t.insert(s, 0);
    }

    t.calculate_answer(true);

    cout << ans.size() << '\n';
    while(!ans.empty()) {
        cout << ans.front() << '\n';
        ans.pop();
    }

    return 0;
}