#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll C;

vector<int> h;
vector<ll> dp;

ll a(int i)
{
    return -2 * h[i];
}

ll b(int i)
{
    return C + dp[i] + (ll)h[i] * h[i];
}

double intersect(int i, int j)
{
    return (double)(b(i) - b(j)) / (a(j) - a(i));
}

ll calculate(int i, int j)
{
    return (ll)(h[i] - h[j]) * (h[i] - h[j]) + C + dp[j];
}

int main(void)
{
    scanf("%d", &N);

    h.resize(N);
    dp.resize(N);

    scanf("%lld", &C);

    for (int i = 0; i < N; i++)
        scanf("%d", &h[i]);

    deque<int> hull;
    dp[0] = 0;
    hull.push_back(0);

    for (int i = 1; i < N; i++) {
        while (hull.size() > 1 && intersect(hull[0], hull[1]) <= h[i]) {
            hull.pop_front();
        }

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

    printf("%lld\n", dp[N - 1]);

    return 0;
}