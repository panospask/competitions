#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MODNUM ((int)1e9 + 7)
#define MOD(val) (val = (((val % MODNUM) + MODNUM) % MODNUM))
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

// General problem variables
int n, m, x, y;
vector<vector<int>> tracks;
vector<ll> dp;
vector<ll> prevdp;
int total_farms;
ll possibilities = 1;
ll lengthsum = 0;

// Forest variables
vector<bool> visited;
vector<vector<pi>> adj_list;

// Tree variables
vector<ll> total_tracklength;
vector<int> tracknum;
vector<vector<int>> dist;
vector<int> members;
int recognize(int node, int par)
{
    members.push_back(node);
    visited[node] = true;
    int ans = 1;
    for (auto& kid : adj_list[node]) {
        if (kid.f != par)
            ans += recognize(kid.f, node);
    }

    return ans;
}

void dfs(int node, int par, int source, int d)
{
    dist[source][node] = d;
    for (auto& kid : adj_list[node])
        if (kid.f != par)
            dfs(kid.f, node, source, d + kid.s);
}

void process_tree(int source, int farm)
{
    total_tracklength[farm] = 0;
    tracknum[farm] = 0;
    tracks[farm].clear();
    members.clear();

    recognize(source, -1);

    for (auto member : members)
        dfs(member, -1, member, 0);

    for (int i = 0; i < members.size(); i++)
        for (int j = i + 1; j < members.size(); j++) {
            ll curdist = dist[members[i]][members[j]];

            if (curdist < y)
                tracks[farm][curdist]++;

            total_tracklength[farm] += curdist;
            MOD(total_tracklength[farm]);
            tracknum[farm]++;
        }

    possibilities *= tracknum[farm];
    MOD(possibilities);
}

ll calc_inv(ll a)
{
    ll c = 1;
    ll b = MODNUM - 2;

    while (b) {
        if (b % 2)
            c = c * a % MODNUM;

        a = a * a % MODNUM;
        b /= 2;
    }

    return c;
}

int main(void)
{
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);

    scanf("%d %d %d %d", &n, &m, &x, &y);
    visited.assign(n, false);
    adj_list.resize(n);
    dist.resize(n, vector<int>(n));
    total_farms = 0;

    for (int i = 0; i < m; i++) {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        a--; b--;
        adj_list[a].push_back(make_pair(b, d));
        adj_list[b].push_back(make_pair(a, d));
    }

    for (int i = 0; i < n; i++) if (!visited[i]) {
        tracks.push_back(vector<int>(y + 1));
        tracknum.push_back(0);
        total_tracklength.push_back(0);
        total_farms++;

        process_tree(i, total_farms - 1);
    }

    for (int farm = 0; farm < total_farms; farm++) {
        lengthsum += total_tracklength[farm] * (possibilities * calc_inv(tracknum[farm]) % MODNUM) % MODNUM;
        MOD(lengthsum);
    }
    lengthsum += possibilities * x * total_farms;
    MOD(lengthsum);

    y = y - (total_farms) * x;

    bool allcount = false;
    if (y < 0)
        allcount = true;

    if (allcount) {
        ll pos = 1;
        for (int i = 1; i <= total_farms - 1; i++) {
            pos = pos * 2 * i;
            MOD(pos);
        }

        ll ans = lengthsum * pos % MODNUM;
        printf("%lld\n", ans);
        return 0;
    }

    prevdp.assign(y + 1, 0);
    dp.assign(y + 1, 0);
    prevdp[0] = 1;

    for (int farm = 0; farm < total_farms; farm++) {
        for (int l = 0; l < y; l++) {
            if (tracks[farm][l] == 0)
                continue;
            for (int prevl = 0; prevl < y - l; prevl++) {
                if (prevdp[prevl] == 0)
                    continue;

                dp[l + prevl] += prevdp[prevl] * tracks[farm][l];
                MOD(dp[l + prevl]);
            }
        }

        swap(dp, prevdp);
        dp.assign(y + 5, 0);
    }

    for (int l = 0; l < y; l++) {
        lengthsum -= (prevdp[l]) * (l + x * total_farms);
        MOD(lengthsum);
    }

    // Finally have the real lengthsum, I think??
    // Calculate all the possibilities for endpoints

    ll pos = 1;
    for (int i = 1; i <= total_farms - 1; i++) {
        pos = pos * 2 * i;
        MOD(pos);
    }


    ll ans = lengthsum * pos % MODNUM;

    printf("%lld\n", ans);
    return 0;
}