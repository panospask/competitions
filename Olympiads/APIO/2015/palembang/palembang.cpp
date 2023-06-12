#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct MedianCost {

    int median = 0;
    multiset<int, greater<int>> smaller;
    multiset<int> larger;
    ll cost = 0;

    void balance(void) {
        if (smaller.size() > larger.size() + 1) {
            larger.insert(median);
            smaller.erase(smaller.begin());

            int new_median = *smaller.begin();

            int change = abs(median - new_median);

            cost += (ll)larger.size() * change;
            cost -= (ll)smaller.size() * change;

            median = new_median;
        }
        else if (larger.size() > smaller.size()) {
            int new_median = *larger.begin();

            int change = abs(median - new_median);

            cost -= (ll)larger.size() * change;
            cost += (ll)smaller.size() * change;

            larger.erase(larger.begin());
            smaller.insert(new_median);
            median = new_median;
        }
    }

    void insert(int a) {
        cost += abs(median - a);

        if (!smaller.empty() && *smaller.begin() >= a)
            smaller.insert(a);
        else
            larger.insert(a);

        balance();
    }

    void erase(int a) {
        cost -= abs(median - a);
        if (larger.find(a) != larger.end())
            larger.erase(larger.find(a));
        else {
            smaller.erase(smaller.find(a));

            int new_median = *smaller.begin();
            int change = abs(median - new_median);

            cost += change * larger.size();
            cost -= change * smaller.size();

            median = new_median;
        }

        balance();
    }
};

int n, k;
vector<pi> v;
ll init_boost;
ll ans = 0;
MedianCost a, b;

bool sumsort(const pi& a, const pi& b)
{
    return a.f + a.s < b.f + b.s;
}

int main(void)
{
    scanf("%d %d", &k, &n);

    for (int i = 0; i < n; i++) {
        char p, q;
        int h, off;

        scanf(" %c %d %c %d", &p, &h, &q, &off);
        if (p == q)
            init_boost += abs(off - h);
        else
            v.push_back(mp(h, off));
    }

    n = v.size();
    sort(v.begin(), v.end(), sumsort);

    for (int i = 0; i < n; i++) {
        a.insert(v[i].f);
        a.insert(v[i].s);
    }

    ans = a.cost;
    if (k == 1) {
        ans += init_boost + n;
        printf("%lld\n", ans);

        return 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        a.erase(v[i].f);
        a.erase(v[i].s);
        b.insert(v[i].f);
        b.insert(v[i].s);

        ans = min(ans, a.cost + b.cost);
    }

    ans += init_boost + n;
    printf("%lld\n", ans);

    return 0;
}