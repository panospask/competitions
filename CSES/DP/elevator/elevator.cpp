#include <bits/stdc++.h>
#define MAXN 20
#define CHECK_BIT(var, pos) (var & (1<<pos))
#define mp make_pair

using namespace std;

typedef pair<int , long long int> il;

int n, x;
il dp[(1<<MAXN)];
int w[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &w[i]);

    for (int i = 0; i < (1<<n); i++)
        dp[i] = mp(1e9, 0); // Many rides

    // First ride, no weight
    dp[0] = mp(1, 0);
    for (int s = 0; s < (1<<n); s++) {
        if (dp[s].first == 1e9)
            continue;

        for (int i = 0; i < n; i++) {
            if (!CHECK_BIT(s, i)) {
                int rides = dp[s].first;
                long long int new_weight = dp[s].second + w[i];
                if (new_weight > x) {
                    // Create new elevator ride
                    new_weight = w[i];
                    rides++;
                }

                dp[s + (1<<i)] = min(dp[s + (1<<i)], mp(rides, new_weight));
            }
        }
    }

    printf("%d\n", dp[(1<<n) - 1].first);
    return 0;
}
