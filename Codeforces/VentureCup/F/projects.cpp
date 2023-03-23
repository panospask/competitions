    #include <bits/stdc++.h>
    #define MAXN 200
    #define MAXK 1000
    #define MOD ((int)1e9 + 7)
    #define OFFSET MAXK * 10
     
    using namespace std;
     
    // dp[i][j][x]: Number of teams using i participants, with j unfinished teams and x penalty
    long long int dp[2][MAXN + 1][OFFSET + MAXK + 1];
    int n, k;
    int students[MAXN + 1];
     
    int main(void)
    {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &students[i]);
        sort(students, students + n);
     
        dp[0][0][OFFSET] = 1; // We can have no participants and no teams
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n - i; j++) // At most n - i open teams allowed, as we won't be able to close more than that
                for (int x = 0; x <= OFFSET + k; x++) {
                    if (dp[0][j][x] == 0) continue;
     
                    // Add the current participant to a team of his own
                    dp[1][j][x] += dp[0][j][x];
                    dp[1][j][x] %= MOD;
     
                    // Add the current participant to an already existing team WITHOUT closing it
                    if (j <= n - (i + 1)) {// Check that it is worth it to do so
                        dp[1][j][x] += (j * dp[0][j][x]) % MOD; // j possible teams to add
                        dp[1][j][x] %= MOD;
                    }
     
                    // Add the current participant to an already existing team AND close it
                    if (j > 0 && OFFSET + k >= x + students[i]) { // Check that it is within the penalty limit( can never actually reduce the penalty)
                        dp[1][j - 1][x + students[i]] += (j * dp[0][j][x]) % MOD;
                        dp[1][j - 1][x + students[i]] %= MOD;
                    }
     
                    // Create a new team with the current participant
                    if (j + 1 <= n - (i + 1)) { // Check that it is worth it to do so
                        dp[1][j + 1][x - students[i]] += dp[0][j][x];
                        dp[1][j + 1][x - students[i]] %= MOD;
                    }
                } 
     
            for (int j = 0; j <= n; j++)
                for (int x = 0; x<= OFFSET + k; x++) {
                    dp[0][j][x] = dp[1][j][x];
                    dp[1][j][x] = 0;
                }
        }
     
        long long int ans = 0;
        for (int x = OFFSET; x <= OFFSET + k; x++) {
            ans += dp[0][0][x];
            ans %= MOD;
        }
     
        printf("%lld\n", ans);
        return 0;
    }