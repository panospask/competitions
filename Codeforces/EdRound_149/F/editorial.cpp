#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector<int> a;

bool gcomp(const int& a, const int& b)
{
    return a > b;
}

bool is_enough(ll x)
{
    multiset<int, decltype(gcomp)*> f(gcomp), s(gcomp);
    multiset<int> remaining;

    ll time_taken_s = 0, time_taken_f = 0;
    int elements_s = 0, elements_f = 0;
    for (int i = 0; i < n; i++) {
        remaining.insert(a[i]);
    }
    while (!remaining.empty() && time_taken_s + *remaining.begin() <= x) {
        auto it = remaining.begin();
        time_taken_s += *it;
        s.insert(*it);
        elements_s++;
        remaining.erase(it);
    }

    if (elements_f + elements_s >= k)
        return true;

    // Iterate over all possibilities
    for (int i = 0; i < n; i++) {
        auto it = s.find(a[i]);
        if (it != s.end()) {
            s.erase(it);
            time_taken_s -= a[i];
            elements_s--;
            while (!remaining.empty() && time_taken_s + *remaining.begin() <= x) {
                auto it = remaining.begin();
                time_taken_s += *it;
                elements_s++;
                s.insert(*it);
                remaining.erase(it);
            }
        }
        else {
            remaining.erase(remaining.find(a[i]));
        }

        if (a[i] + time_taken_f <= x) {
            f.insert(a[i]);
            time_taken_f += a[i];
            elements_f++;
        }
        else if (a[i] < *f.begin()) {
            time_taken_f += a[i] - *f.begin();
            f.erase(f.begin());
            f.insert(a[i]);
        }

        if (elements_f + elements_s >= k)
            return true;
    }

    return false;
}

void solve(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    ll l = 0;
    ll r = 1;
    while (!is_enough(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (is_enough(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%lld\n", r);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}