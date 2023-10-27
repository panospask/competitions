#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int A, B, C;

vector<int> x;
vector<ll> pref;
vector<ll> dp;

deque<int> hull;

// Calculate value at i using line j
ll calculate(int i, int j)
{
    int x = pref[i] - pref[j];

    return (ll)x * x * A + (ll)x * B + C + dp[j];
}

// Where do lines i and j intersect

ll lam(int i)
{
    return B - 2 * pref[i] * A;
}
ll cons(int i)
{
    return (ll)pref[i] * pref[i] * A - (ll)pref[i] * B + C + dp[i];
}

double intersect(int i, int j)
{
    return (double)(cons(i) - cons(j)) / (lam(j) - lam(i));
}

int main(void)
{
    scanf("%d", &N);
    scanf("%d %d %d", &A, &B, &C);

    x.resize(N);
    pref.resize(N + 1);
    dp.resize(N + 1);

    dp[0] = 0;
    pref[0] = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
        pref[i + 1] = pref[i] + x[i];
    }

    hull.push_back(0);

    for (int i = 1; i <= N; i++) {
        while (hull.size() > 1 && intersect(hull[0], hull[1]) <= pref[i])
            hull.pop_front();

        dp[i] = calculate(i, hull.front());

        while (hull.size() > 1) {
            int sz = hull.size();
            if (intersect(hull[sz - 1], hull[sz - 2]) >= intersect(i, hull[sz - 1]))
                hull.pop_back();
            else
                break;
        }

        hull.push_back(i);
    }

    printf("%lld\n", dp[N]);

    return 0;
}