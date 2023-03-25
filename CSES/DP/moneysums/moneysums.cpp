#include <bits/stdc++.h>
#define MAXS (int)1e5
#define MAXN 100

using namespace std;

bool can_make[MAXS + 2];
int n;
int coins[MAXN + 2];

vector<int> ans;

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    sort(coins, coins + n);

    can_make[0] = true; // I can make 0 by not using any coins
    for (int i = 0; i < n; i++) {
    for (int s = MAXS - 1; s >= 0 ; s--)
        if (can_make[s]) {
            if (s + coins[i] <= MAXS)
                can_make[s + coins[i]] = true;
        }
    }
    for (int i = 1; i <= MAXS; i++)
        if (can_make[i])
            ans.push_back(i);

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}