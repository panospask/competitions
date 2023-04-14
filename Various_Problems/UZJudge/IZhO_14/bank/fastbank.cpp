#include <bits/stdc++.h>
#define MAXN 20
#define CHECK_BIT(var, pos) (var & (1<<pos))

using namespace std;

int n, m;

// dp[i]: The maximum prefix of people we can pay with the subset i
int dp[(1<<MAXN)];
// leftovers[i]: How much money is leftovers after paying the dp[i] people
int leftovers[(1<<MAXN)];

int reqs[MAXN + 2];
int notes[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &reqs[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &notes[i]);

    memset(dp, -1, sizeof(dp));
    memset(leftovers, -1, sizeof(leftovers));
    dp[0] = 0;
    leftovers[0] = 0;

    for (int s = 0; s < (1<<m); s++) {
        if (dp[s] == -1) 
            continue;
        if (dp[s] == n) {
            printf("YES\n");
            return 0;
        }

        int to_cover = reqs[dp[s]];
        for (int i = 0; i < m; i++) {
            if (CHECK_BIT(s, i))
                continue;
            
            // Use i as the last banknote
            int val = notes[i];
            if (val + leftovers[s] < to_cover) {
                dp[s + (1<<i)] = dp[s];
                leftovers[s + (1<<i)] = leftovers[s] + val;
            }
            else if (val + leftovers[s] == to_cover) {
                dp[s + (1<<i)] = dp[s] + 1;
                leftovers[s + (1<<i)] = 0;
            }
        }
    }

    printf("NO\n");
    return 0;
}