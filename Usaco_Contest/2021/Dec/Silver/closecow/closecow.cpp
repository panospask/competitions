#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200000

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int BIG = 1e9;

struct Range {
    int l, r;
    ll sum, best;
    vector<pi> points;

    void init(int l, int r) {
        this->l = l;
        this->r = r;
    }
    void insert(pi a) {
        points.pb(a);
    }

    // Don't call
    int dist(int i) {
        return points[i].first - l;
    }

    // Call after completion
    void calculate(void) {
        sort(points.begin(), points.end());

        int j = 0;
        best = 0;
        ll cur = 0;
        for (int i = 0; i < points.size(); i++) {
            sum += points[i].second;

            double fin = 2 * dist(i) - 0.5 + (double)(r - l - 2 * dist(i) - 0.5) / 2;
            while (j < points.size() && dist(j) < fin) {
                cur += points[j].second;
                j++;
            }

            best = max(best, cur);
            cur -= points[i].second;
        }
    }
};

int N, K, M;
vector<pi> patches;
vector<int> opponents;
vector<Range> ranges;

int main(void)
{
    scanf("%d %d %d", &K, &M, &N);

    patches.resize(K);
    opponents.resize(M);
    ranges.resize(M - 1);

    for (int i = 0; i < K; i++) {
        scanf("%d %d", &patches[i].first, &patches[i].second);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &opponents[i]);
    }

    sort(patches.begin(), patches.end());
    sort(opponents.begin(), opponents.end());

    int patch = 0;
    ll first = 0, last = 0;
    for (int i = 0; i < M; i++) {
        if (i) {
            ranges[i - 1].init(opponents[i - 1], opponents[i]);
        }

        while (patch < K && patches[patch].first < opponents[i]) {
            if (i == 0) {
                first += patches[patch].second;
            }
            else {
                ranges[i - 1].insert(patches[patch]);
            }
            patch++;
        }
    }
    while (patch < K) {
        last += patches[patch].second;
        patch++;
    }

    vector<ll> res = {first, last};
    for (int i = 0; i < M - 1; i++) {
        ranges[i].calculate();
        res.pb(ranges[i].best);
        res.pb(ranges[i].sum - ranges[i].best);
    }

    sort(res.rbegin(), res.rend());
    ll ans = 0;
    for (int i = 0; i < min((int)res.size(), N); i++) {
        ans += res[i];
    }

    printf("%lld\n", ans);

    return 0;
}