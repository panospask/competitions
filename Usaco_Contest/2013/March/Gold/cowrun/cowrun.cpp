#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;

//dp[i][j][k]: The minimum cost of stopping i cows from the left and j from the right
// You at at pos[i] if k = 0 and pos[j] if k = 1
long long int dp[MAXN + 2][MAXN + 2][2];
int n;
int rightcows[MAXN + 2];
int leftcows[MAXN + 2];
int l = 1, r = 1;

int main(void)
{
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);

    scanf("%d", &n);
    int cow;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cow);
        if (cow < 0)
            leftcows[l++] = cow;
        else 
            rightcows[r++] = cow;
    }
    l--; r--;

    // Sort by closeness to fj
    sort(leftcows + 1, leftcows + l + 1);
    reverse(leftcows + 1, leftcows + l + 1);

    sort(rightcows + 1, rightcows + r + 1);

    for (int i = 0; i <= l; i++)
        for (int j = 0; j <= r; j++)
            for (int k = 0; k <= 1; k++)
                dp[i][j][k] = 1e13;

    dp[0][0][0] = dp[0][0][1] = 0; // Initial position, no damage
    for (int i = 0; i <= l; i++)
        for (int j = 0; j <= r; j++) {
            // Two cases: We are at the leftmost or at the rightmost cow
            
            int lpos = leftcows[i];
            int rpos = rightcows[j];
            int remcows = l - i + r - j;

            // Go left
            if (i + 1 <= l) {
                int curpos = leftcows[i+1];
                dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][0] + abs(curpos - lpos) * remcows);
                dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][1] + abs(curpos - rpos) * remcows);
            }
            // Go right
            if (j + 1 <= r) {
                int curpos = rightcows[j+1];
                dp[i][j+1][1] = min(dp[i][j+1][1], dp[i][j][0] + abs(curpos - lpos) * remcows);
                dp[i][j+1][1] = min(dp[i][j+1][1], dp[i][j][1] + abs(curpos - rpos) * remcows);
            }
        }

    long long ans = min(dp[l][r][0], dp[l][r][1]);
    printf("%lld\n", ans);
    return 0;
}