#include <bits/stdc++.h>
#include "biscuits.h"
#define CHECK_BIT(val, pos) ((val) & (1ll << pos))

using namespace std;


typedef long long ll;

const int MAXV = 1e5 + 1;
const ll TOTALMAX = 1e18;
const int N = 60;

ll X;
vector<ll> A;

ll subtask1(void)
{
    ll ans = 1;

    ll tot = 0;
    for (int i = 0; i < N; i++) {
        ll target = (1ll << i);

        if (tot + A[i] * target >= target) {
            ans *= 2;
            tot += (A[i] - 1) * target;
            A[i] = 1;
        }
        else {
            // Take what is missing in order to complete the number
            ll rem = target - tot;
            ll add = 1;

            for (int j = i; j >= 0; j--) {
                if (A[j]) {
                    if (rem > 0)
                        rem -= (1ll << j);
                    else
                        add *= 2;
                }
            }

            if (rem <= 0)
                ans += add;
        }
    }

    return ans;
}

bool can_make(ll v)
{
    vector<ll> tmp = A;

    for (int i = 0; i < N; i++) {
        if (CHECK_BIT(v, i)) {
            if (tmp[i] >= X)
                tmp[i] -= X;
            else
                return false;
        }

        if (i != N - 1)
            tmp[i + 1] += tmp[i] / 2;
    }

    return true;
}

ll count_tastiness(ll x, vector<ll> a)
{
    A = a;
    A.resize(N);
    X = x;

    if (x == 1) {
        return subtask1();
    }

    ll ans = 0;
    for (int v = 0; v < MAXV; v++)
        if (can_make(v))
            ans++;

    return ans;
}