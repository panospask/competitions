#include <bits/stdc++.h>
#define MAXN (int)(10e5+10)

using namespace std;

int t, k, n;
char patch[MAXN];
char cow[MAXN];

void solve(void)
{
    scanf("%d %d", &n, &k);

    getchar();
    for (int i = 0; i < n; i++) {
        cow[i] = getchar();
        patch[i] = '.';
    }

    int curplace;
    int maxpatch = 0;
    unordered_map<char, int> prev;
    prev['H'] = -1;
    prev['G'] = -1;
    int dist;
    for (int i = 0; i < n; i++) {
        dist = abs(prev[cow[i]] - i);
        if (abs(prev[cow[i]] - i) > k || prev[cow[i]] == -1) {
            curplace = min(i + k, n - 1);
            if (patch[curplace] != '.' && curplace == n - 1)
                curplace--;
            patch[curplace] = cow[i];
            prev[cow[i]] = curplace;
            maxpatch++;
        } 
    }

    printf("%d\n", maxpatch);
    for (int i = 0; i < n; i++)
        putchar(patch[i]);
    putchar('\n');

    return;
}

int main(void)
{
    scanf("%d", &t);

    for (int x = 0; x < t; x++) 
        solve();

    return 0;
}