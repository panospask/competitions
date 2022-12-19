#include <bits/stdc++.h>
#define MAXN 20
#define MAXK 10
#define pb push_back

using namespace std;

bool overperformed[MAXN][MAXN];
int n, k;

int main(void)
{
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    scanf("%d %d", &k, &n);
    vector<int> cows;
    for (int t = 0; t < n; t++) {
        int curcow;
        for (int i = 0; i < n; i++) {
            scanf("%d", &curcow);
            cows.pb(curcow - 1);
        } 

        for (int i = 0; i < n; i++) 
            for (int j = i + 1; j < n; j++)
                overperformed[cows[i]][cows[j]] = true;
        cows.clear(); 
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!overperformed[i][j] && i != j)
                ans++;

    printf("%d\n", ans);
    return 0;
}