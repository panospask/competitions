#include <bits/stdc++.h>
#define MAXVAL (500*250)
#define MOD ((int)1e9 + 7)

using namespace std;

long long int total_pos[MAXVAL + 2];
int x;

long long int calc_power(long long int a, long long int b, int mod)
{
    a %= mod;
    long long int c = 1;

    while (b > 0) {
        if (b % 2)
            c = c * a % mod;
        
        a = a * a % mod;
        b /= 2;
    }

    return c;
}

int main(void)
{
    scanf("%d", &x);

    long long int sum = x * (x + 1) / 2;
    if (sum % 2) {
        printf("0\n");
        return 0;
    }

    long long int target = sum / 2;
    total_pos[0] = 1; // Only 1 possibility to create sum 0, the empty set
    for (int i = 1; i <= x; i++)
        for (int s = target - i; s >= 0; s--) {
            total_pos[s + i] = (total_pos[s + i] + total_pos[s]) % MOD;
        }

    long long int ans = (total_pos[target] * calc_power(2, MOD - 2, MOD)) % MOD;
    printf("%lld\n", ans);
    return 0;
}