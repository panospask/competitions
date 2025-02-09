#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 9;

// Very big number
const int INF = 1e9 + 5;

int S, X, Y;
int target_A = INF, target_B = INF;

ll calc_pow(ll a, int b)
{
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

// Is it possible to reach the target when traversing the sequences with length <= v
bool possible(int v)
{
    return 2 * v - 1 >= target_A || v >= target_B;
}

int main(void)
{
    freopen("shroompath.in", "r", stdin);
    freopen("shroompath.out", "w", stdout);

    int type;
    scanf("%d", &type);
    scanf("%d %d %d", &S, &X, &Y);

    // How many A (respectively B) mushrooms we have to gather
    if (X > 0) {
        target_A = ((S - 1) / X) + 1;
    }
    if (Y > 0) {
        target_B = ((S - 1) / Y) + 1;
    }

    int l = 0;
    int r = S; //Always completable with the sequences of length <= S
    while (l + 1 < r) {
        int mid = (l + r) / 2;

        if (possible(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    // Sequences of length r are required
    // Total steps to reach the sequence of length r
    int prv = r - 1;
    // The sum of k * 2^k from 1 to prv
    ll total_steps = ((prv - 1) * calc_pow(2, prv + 1) + 2) % MOD;

    if (2 * r - 1 >= target_A) {
        total_steps = (total_steps + target_A) % MOD;
    }
    else {
        total_steps = (total_steps +  r * calc_pow(2, prv) + 1) % MOD;
    }

    printf("%lld\n", total_steps);

    return 0;
}