#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int BIG = 1e9;

int N;
int MAXA;
vector<pi> monsters;
vector<int> beg;
vector<int> a;
set<pi> ranges;

// Number of ranges by damage dealt
vector<int> rangenumber;
// Array to take prefix sums on in order to form rangenumber
vector<int> rangeder;

int main(void)
{
    scanf("%d", &N);

    MAXA = 0;
    monsters.resize(N);
    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &monsters[i].first);
        a[i] = monsters[i].first;
        monsters[i].second = i;

        MAXA = max(MAXA, monsters[i].first);
    }

    beg.resize(N);
    for (int i = 0; i < N; i++) {
        beg[i] = a[i];
    }

    sort(monsters.begin(), monsters.end());

    ranges.insert(mp(0, N-1));
    beg[0] = 0;

    for (int i = 0; i < N; i++) {
        int cur_dmg = monsters[i].first;
        int cur_mon = monsters[i].second;

        // Find the range that contains the current monster
        auto it = ranges.upper_bound(mp(cur_mon, BIG));
        it--;

        pi cur_range = *it;
        ranges.erase(it);

        // Split current range into 2
        pi r1 = mp(cur_range.first, cur_mon - 1);
        pi r2 = mp(cur_mon + 1, cur_range.second);

        if (r1.first <= r1.second) {
            ranges.insert(r1);
        }
        if (r2.first <= r2.second) {
            beg[r2.first] = cur_dmg;
            ranges.insert(r2);
        }
    }

    rangeder.resize(MAXA + 1);
    rangenumber.resize(MAXA + 1);

    for (int i = 0; i < N; i++) {
        rangeder[beg[i]]++;
        rangeder[a[i]]--;
    }
    // Take prefix sums
    rangenumber[0] = 1;
    for (int i = 1; i <= MAXA; i++) {
        rangenumber[i] = rangenumber[i - 1] + rangeder[i];
    }

    for (int d = 1; d <= MAXA; d++) {
        ll ans = 0;
        for (int v = 0; v < MAXA; v += d) {
            ans += rangenumber[v];
        }

        printf("%lld ", ans);
    }
    printf("\n");

    return 0;
}