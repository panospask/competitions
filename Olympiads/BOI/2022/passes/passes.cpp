#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e18;

string s;
int N, G;
vector<vector<int>> spots;
vector<int> group;

vector<vector<ll>> optimal;

vector<vector<vector<ll>>> pref, suff;

vector<ll> self;

// We take to the left everything up to but NOT including spots[g][cut]
ll cost(int m, int g, int cut) {
    ll ans = 0;

    for (int b = 0; b < G; b++) {
        if (CHECK_BIT(m, b)) {
            ans += 2 * suff[g][cut][b];
            ans += 2 * pref[g][cut][b];
        }
    }

    ans += self[cut] + self[spots[g].size() - cut];
    return ans;
}

void calculate(int g, int mask) {
    // Goal is to find first step that becomes increasing
    int l = -1;
    int r = spots[g].size();

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (cost(mask, g, mid) > cost(mask, g, mid + 1)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    optimal[g][mask] = cost(mask, g, r);
}

int main(void) {
    cin >> s;
    N = s.size();
    group.resize(N);

    vector<int> allgroups;
    for (int i = 0; i < N; i++) {
        group[i] = s[i] - 'A';
        allgroups.pb(group[i]);
    }
    sort(allgroups.begin(), allgroups.end());
    allgroups.resize(unique(allgroups.begin(), allgroups.end()) - allgroups.begin());
    G = allgroups.size();
    for (int i = 0; i < N; i++) {
        group[i] = lower_bound(allgroups.begin(), allgroups.end(), group[i]) - allgroups.begin();
    }

    spots.resize(G);
    self.resize(N + 1);
    optimal.assign(G, vector<ll>(1 << G, 0));

    for (int i = 0; i < N; i++) {
        spots[group[i]].pb(i);
    }

    self[1] = 0;
    for (int i = 2; i <= N; i++) {
        self[i] = self[i - 1] + i - 1;
    }

    pref.resize(G);
    suff.resize(G);
    for (int g = 0; g < G; g++) {
        // Start with nothing left, everything right
        pref[g].resize(spots[g].size() + 1, vector<ll>(G, 0));
        suff[g].resize(spots[g].size() + 1, vector<ll>(G, 0));

        vector<ll> cntsuff(G);
        vector<ll> cntpref(G);

        // Calculate suffix first
        for (int p = N - 1; p >= 0; p--) {
            cntsuff[group[p]]++;

            if (group[p] == g) {
                for (int b = 0; b < G; b++) {
                    suff[g][0][b] += cntsuff[b];
                }
            }
        }

        // Now update position by position
        int p = 0;
        
        for (int i = 0; i < spots[g].size(); i++) {
            while (p < spots[g][i]) {
                cntpref[group[p]]++;
                cntsuff[group[p]]--;
                p++;
            }

            for (int b = 0; b < G; b++) {
                pref[g][i + 1][b] = pref[g][i][b] + cntpref[b];
                suff[g][i + 1][b] = suff[g][i][b] - cntsuff[b];
            }
        }

        // Now calculate optimality
        for (int mask = 0; mask < (1 << G); mask++) {
            if (!CHECK_BIT(mask, g)) {
                calculate(g, mask);
            }
        }
    }

    vector<ll> dp(1 << G, INF);
    dp[0] = 0;
    for (int s = 1; s < (1 << G); s++) {
        for (int b = 0; b < G; b++) {
            if (CHECK_BIT(s, b)) {
                int prv = s - (1 << b);
                dp[s] = min(dp[s], dp[prv] + optimal[b][prv]);
            }
        }
    }

    printf("%lf\n", (double)dp[(1 << G) - 1] / 2);

    return 0;
}