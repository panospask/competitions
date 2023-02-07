#include <bits/stdc++.h>
#define MAXS 1000000

using namespace std;

string s, t;
int nxt[MAXS];
int prv[MAXS];
int strt;

vector<int> pi;

void pref_func(void)
{
    pi.resize(t.size());
    pi[0] = 0;

    for (int i = 1; i < t.size(); i++) {
        int j = pi[i - 1];
        while (t[j] != t[i] && j != 0)
            j = pi[j - 1];

        if (t[j] == t[i])
            pi[i] = j;
        else 
            pi[i] = 0;
    }

    return;
}

void del_str(int i, int j)
{
    int begin = prv[i];
    int nd = nxt[j];
    if (begin == -1)
        strt = nd;
    else 
        nxt[begin] = nd;
    prv[nd] = begin;
}

void find_strings(void)
{
    int n = t.size();
    int q = 0;
    int i = 0;
    int nstart = 0;

    while (i < s.size()) {
        while (s[i] != t[q] && q != 0)
            q = pi[q - 1];
        
        if (s[i] == t[q]) {
            if (q == 0) 
                nstart = i;
            q++;
        }
        if (q == n) {
            del_str(nstart, i);
            i = nxt[i];
            for (int j = 0; j < n; j++) {
                if (i == -1)
                    break;
                i = prv[i];
                q = 0;
            }
        }

        if (i == -1)
            i = strt;
        else 
            i = nxt[i];
    }
}

void prnt_string(void)
{
    int i = strt;
    while (i < s.size()) {
        putchar(s[i]);
        i = nxt[i];
    }
    printf("\n");
}

int main(void)
{
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    cin >> s >> t;

    for (int i = 0; i < s.size(); i++) {
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }
    strt = 0;

    pref_func();
    find_strings();
    prnt_string();
}
