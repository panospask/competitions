#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 10000
#define MAXP 2000

using namespace std;

typedef long long int ll;

int n, m;
// dp[p][i]: Permutations of length i using the first p primes
long long int dp[MAXP + 2][MAXN + 2];
bool iscomposite[MAXN + 5];
vector<int> primes;

int main(void)
{
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; i++) 
        if (!iscomposite[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= n; j+= i)
                iscomposite[j] = true;
        }
    if (primes.size() == 0) {
        printf("%d\n", 1);
        return 0;
    }

    for (int j = 0; j <= n; j++)
        dp[0][j] = 1;

    for (int i = 1; i <= primes.size(); i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = dp[i-1][j];

            long long int curprime_power = primes[i-1];
            while (curprime_power <= j) {
                long long int to_add = curprime_power * dp[i-1][j - curprime_power] % m;
                dp[i][j] = (dp[i][j] + to_add) % m;

                curprime_power *= primes[i-1];
            }
        }
    }

    printf("%lld\n", dp[primes.size()][n]);
    return 0;
}