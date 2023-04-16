#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 5000
#define BUMP 1000000

using namespace std;

typedef pair<int, int> ii;

int n, q;

// NOTE: Vectors save time
// NOTE: Memset in arrays is time wasting, we would rather do less updates by hand 
// dp[l][r]: The number of 3sum tuples in the range (l, r)
vector<vector<long long>> dp(MAXN, vector<long long>(MAXN, 0));
int a[MAXN];
vector<int> freq(2 * BUMP + 1);

int main(void)
{
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);

    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i] += BUMP;

        if (a[i] <= 0 || a[i] >= 2 * BUMP) {
            cerr << 2 * BUMP << endl;
            cerr << a[i] << endl;
            exit(1);
        }
    }

    // Calculate the triplets containing l, r, and something in the middle for all l, r
    for (int l = n - 2; l >= 0; l--) {
        freq[a[l+1]]++;
        for (int r = l + 2; r < n; r++) {
            int val = -(a[l] + a[r]) + 3 * BUMP;
            if (val <= 2 * BUMP && val >= 0)
                dp[l][r] = freq[val];
            freq[a[r]]++;
        }
        for (int r = l + 1; r < n; r++)
            freq[a[r]]--;
    }

    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;

            if (len <= 2) {
                // What 3sum? We only have 2 numbers
                dp[l][r] = 0;
                continue;
            }

            // Add the 3sun tuples from (l, r - 1), (l + 1, r) and remove the common ones
            dp[l][r] += dp[l][r-1] - dp[l+1][r-1] + dp[l+1][r]; 
        }

    int l, r;
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l, &r);
        l--; r--;

        printf("%lld\n", dp[l][r]);
    }

    return 0;
}