#include <bits/stdc++.h>
#define MAXN 2000

using namespace std;

map<char ,int> arraypos;
char s[MAXN + 2];

void solve(void)
{
    int n;
    scanf("%d", &n);

    arraypos.clear();
    getchar();
    bool isgood = true;
    for (int i = 0; i < n; i++) {
        s[i] = getchar();
        if (arraypos.count(s[i])) {
            if (arraypos[s[i]] != i % 2)
                isgood = false;
        }
        else 
            arraypos[s[i]] = i % 2;

        // cout << s[i];
    }

    if (isgood)
        printf("YES\n");
    else 
        printf("NO\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) 
        solve();
}