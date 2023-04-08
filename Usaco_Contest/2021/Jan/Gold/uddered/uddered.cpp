#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20
#define CHECK_BIT(var, pos) (var & (1<<pos))

using namespace std;

// dp[i]: The minimum number of flipped letters for the set
int dp[(1<<20)];
int n;
string s;

// adjacent[i][j]: Number of times that i-th letter appears directly before j-th letter
int adjacent[MAXN + 2][MAXN + 2];
map<char, int> comp;
int cur = 0;

int main(void)
{
    // freopen("uddered.in", "r", stdin);
    // freopen("uddered.out", "w", stdout);

    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (comp.find(s[i]) == comp.end()) {
            comp[s[i]] = cur++;
        }
    }

    for (int i = 1; i < n; i++) {
        adjacent[comp[s[i-1]]][comp[s[i]]]++;
    }

    dp[0] = 1; // Sung at least one time
    n = cur;
    for (int i = 1; i < (1<<n); i++) {
        dp[i] = INT_MAX;
    }

    for (int s = 0; s < (1<<n); s++) {
        if (dp[s] == INT_MAX)
            break;

        for (int i = 0; i < n; i++) {
            // Try to add letter i AT THE END OF THE ALPHABET
            if (!CHECK_BIT(s, i)) {
                int val = dp[s];
                for (int j = 0; j < n; j++) {
                    if (CHECK_BIT(s, j) || i == j)
                        val += adjacent[i][j];
                }

                dp[s + (1<<i)] = min(dp[s + (1<<i)], val);
            }
        }
    }

    int ans = dp[(1<<n)-1];
    printf("%d\n", ans);
    return 0;
}