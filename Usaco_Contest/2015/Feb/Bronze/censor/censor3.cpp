#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int main(void)
{
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    

    string s, t;
    char c = getchar();;
    while (c != '\n') {
        s.pb(c);
        c = getchar();
    }
    c = getchar();
    while (c != '\n') {
        t.pb(c);
        c = getchar();
    }

    string fin = "";
    int n = t.size();

    for (char c : s) {
        fin.push_back(c);
        if (fin.size() >= n && fin.substr(fin.size() - n) == t) {
            fin.resize(fin.size() - n);
        }
    }

    for(auto c : fin) 
        putchar(c);
    putchar('\n');

    return 0;
}