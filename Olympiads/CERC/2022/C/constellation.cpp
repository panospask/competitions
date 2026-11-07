#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXN = 2e3;

int N;
// Initial stars
vector<pi> stars;

// sum of distances from A to B
// I only need to fill up above the main diagonal (if needed use this)
ll sum[MAXN][MAXN];

// Is some constellation active
vector<bool> active;
// size of each constellation
vector<int> cnt;
vector<int> age;

struct Merge {
    int a;
    int b;

    ll s = 0;
    int t1, t2 = 0;
    int c1, c2 = 0;

    Merge(int x, int y) {
        // Make (x, y) equal to (y, x)
        a = min(x, y);
        b = max(x, y);

        s = sum[a][b];
        t1 = min(age[a], age[b]);
        t2 = max(age[a], age[b]);
        c1 = cnt[a];
        c2 = cnt[b];
    }
};

priority_queue<Merge, vector<Merge>, greater<Merge>> mergers;

int t = 0;

bool operator > (const Merge& u, const Merge& v) {
    if ((ll)v.c1 * v.c2 * u.s != (ll)u.c1 * u.c2 * v.s) {
        return (ll)v.c1 * v.c2 * u.s > (ll)u.c1 * u.c2 * v.s;
    }
    if (u.t1 != v.t1) {
        return u.t1 > v.t1;
    }
    return u.t2 > v.t2;
}

ll dist(pi a, pi b) {
    return (ll)(a.first - b.first) * (a.first - b.first) + (ll)(a.second - b.second) * (a.second - b.second);
}

int unite(int u, int v) {

    active[v] = false;
    // This is the current age
    age[u] = t++;

    // Move everything that v has to u
    cnt[u] += cnt[v];
    for (int i = 0; i < N; i++) {
        if (active[i] && i != u) {
            // Move the stars of v to u in the sum
            sum[u][i] += sum[v][i];
            sum[i][u] += sum[v][i];
        }
    }
    
    // Insert back the mergers with u
    for (int i = 0; i < N; i++) {
        if (active[i] && i != u) {
            mergers.push(Merge(i, u));
        }
    }

    return cnt[u];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    stars.resize(N);
    age.resize(N);
    cnt.resize(N);
    active.assign(N, true);

    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        stars[i] = {x, y};
        cnt[i] = 1;
        age[i] = t++;
        active[i] = true;
    }

    // Calculate distances
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            sum[i][j] = sum[j][i] = dist(stars[i], stars[j]);
            mergers.push(Merge(i, j));
        }
    }

    while (!mergers.empty()) {
        auto p = mergers.top();
        mergers.pop();
        int u = p.a;
        int v = p.b;
        if ((!active[v]) || (!active[u]) || (sum[u][v] != p.s)) {
            continue;
        }

        int ans = unite(u, v);
        cout << ans << endl;
    }
}