#include <bits/stdc++.h>

using namespace std;

vector<int> pi;
map<int, int> nxts;
map<int, int> prvs;
string t;
string s;

void pref_func(void)
{
    pi.resize(t.size());
    pi[0] = 0;

    for (int i = 1; i < t.size(); i++) {
        int j = pi[i - 1];
        while (t[j] != t[i] && j != 0) {
            j = pi[j - 1];
        }

        if (t[j] == t[i])
            pi[i] = j;
        else 
            pi[i] = 0;
    }

    return;
}

int del_string(int start, int end)
{
    int temp = prvs[start];
    nxts[temp] = nxts[end];
    prvs[nxts[end]] = temp;

    return temp;
}

void find_same_string(void)
{
    int i = 0;
    int j = 0;
    int q = 0;
    int nstart = 0;
    while (i < s.size() && i != -1) {
        while (q > 0 && t[q + 1] != s[i]) 
            q = pi[q];
        if (t[q + 1] == s[i]) { 
            if (q == 0)
                nstart = i;
            q++;
        }
        if (q  == t.size()) {
            del_string(nstart, i);
            i = -1;
        }
        i = nxts[i];
    }
}

void prnt_string(void)
{
    int i = nxts[-1];
    while (i < s.size() && i != -1) {
        putchar(s[i]); 
        i = nxts[i];
    }
    printf("\n");
}

int main(void)
{
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    cin >> s >> t;
    nxts[-1] = 0;
    nxts[s.size()] = -1;
    prvs[-1] = s.size();

    for (int i = 0; i < s.size(); i++) {
        nxts[i] = i + 1;
        prvs[i] = i - 1;
    }

    pref_func();
    find_same_string();
    prnt_string();

    return 0;
}