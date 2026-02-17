#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e9 + 5;

int opt[10000001];

int N, Q;
vector<int> m;

vector<int> pref;
vector<vector<int>> dpref;

vector<int> suff;
vector<vector<int>> dsuff;

int cur = 0;
void find_prefix(int cur) {
    // Find cur
    int l = 0;
    int r = N;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (dpref[mid].back() < m[cur]) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    pref[cur] = r;
    dpref[r].pb(m[cur]);
}

void find_suffix(int cur) {
    // Find cur
    int l = 0;
    int r = N;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (dsuff[mid].back() > m[cur]) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    suff[cur] = r;
    dsuff[r].pb(m[cur]);
}

void change(int t) {
    m[cur] = t;
    find_suffix(cur);
    find_prefix(cur);
}

int main(void) {
    scanf("%d %d", &N, &Q);

    m.resize(N);
    pref.resize(N);
    suff.resize(N);
    dpref.resize(N);
    dsuff.resize(N);

    for (int i = 0; i < N; i++) {
        dpref[i].pb(INF);
        dsuff[i].pb(-INF);
    }
    dpref[0].pb(-INF);
    dsuff[0].pb(INF);


    for (int i = 0; i < N; i++) {
        scanf("%d", &m[i]);
    }

    while (Q--) {
        char c;
        scanf(" %c", &c);

        if (c == '>') {
            find_prefix(cur);
            cur++;
        }
        else if (c == '<') {
            find_suffix(cur);
            cur--;
        }
        else {
            int t;
            scanf("%d", &t);
            change(cur, t);
        }
    }
}