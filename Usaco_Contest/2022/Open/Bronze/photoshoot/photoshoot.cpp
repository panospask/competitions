#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (2 * (int)(10e5))

using namespace std;

int n;
char cowval[MAXN + 2];
int transformed[MAXN + 2];

int main(void)
{
    // freopen("photoshoot.in", "r", stdin);
    // freopen("photoshoot.out", "w", stdout);

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        cowval[i] = getchar();
    }

    // Build the new string
    int sz = 0;
    for (int i = n - 1; i >= 1; i-= 2) {
        if (cowval[i] == cowval[i - 1])
            continue;
        else if (cowval[i] == 'G' && sz % 2 != 0)
            sz++;
        else if (cowval[i] == 'H' && sz % 2 != 1)
            sz++;
    }

    printf("%d\n", sz);
    return 0;
}