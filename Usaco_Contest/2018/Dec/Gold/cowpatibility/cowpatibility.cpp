#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef __int128_t lll;

const int FLAVOURS = 5;
const ll MOD = (1ll << 61) - 1;
const int P = 1111;

int n;
vector<vector<int>> ordered;
vector<map<ll, int>> sharing;
ll curv = 1;
int curlen = 0;

ll ans = 0;

void generate_combos(int pos, int i)
{
    if (pos == ordered[i].size()) {
        if (curv == 60)
            cerr << "here";
        if (curlen % 2 == 0)
            ans += sharing[curlen][curv]++;
        else
            ans -= sharing[curlen][curv]++;
        return;
    }

    // Don't include this
    generate_combos(pos + 1, i);

    // Include this
    ll ol_v = curv;
    curlen++;
    curv = (lll)curv * (P + ordered[i][pos]) % MOD;
    generate_combos(pos + 1, i);
    curlen--;
    curv = ol_v;
}

int main(void)
{
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);

    scanf("%d", &n);

    ordered.resize(n);

    sharing.resize(FLAVOURS + 1);

    for (int i = 0; i < n; i++) {
        ordered[i].resize(FLAVOURS);
        for (int j = 0; j < FLAVOURS; j++)
            scanf("%d", &ordered[i][j]);

        sort(ordered[i].begin(), ordered[i].end());

        curlen = 0;
        curv = 1;
        generate_combos(0, i);
    }

    // ll ans = 0;
    // for (auto& v : sharing) {
    //     ll res = (ll)v.s * (v.s - 1);
    //     if (res == 0)
    //         continue;

    //     cerr << v.f.f << ' ' << v.f.s << ' ' << v.s << endl;

    //     if (v.f.f % 2)
    //         ans -= res;
    //     else
    //         ans += res;
    // }

    // cerr << "DONE" << endl;

    printf("%lld\n", ans);

    return 0;
}