#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20

using namespace std;

int cows[MAXN + 2];
int stalls[MAXN + 2];
int n;

bool greatercomp(int a, int b)
{
    return a > b;
}


int main(void)
{
    // freopen("stalling.in", "r", stdin);
    // freopen("stalling.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &cows[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &stalls[i]);

    sort(cows, cows + n, greatercomp);
    sort(stalls, stalls + n, greatercomp);

    long long int ans = 1;
    int curstall = -1;
    bool isgood = true;
    for (int cow = 0; cow < n && isgood; cow++) {
        while (curstall < n - 1 && stalls[curstall + 1] >= cows[cow])   
            curstall++;
        
        ans *= (curstall + 1 - cow);
    }

    printf("%lld\n", ans);
    return 0;
}