#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

// MOD is slow... without manual add() function to save time, it fails at test cases 7+

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXN = 1e4 * 5;
const int MAXK = 20;

struct Query {
    int a, b;
};
bool operator < (const Query& a, const Query& b)
{
    return mp(a.a, a.b) < mp(b.a, b.b);
}

int Q;
int N, K;
vector<Query> queries;
vector<int> v;
vector<int> initial;
vector<int> ans;
int dp[MAXN][MAXK][MAXK];
int pref[MAXN][MAXK];

void add(int& a, int b)
{
    a += b;
    if (a >= MOD) a -= MOD;
}

void d_c(int l, int r, vector<int>& q)
{
    if (l == r - 1) {
        for (auto v : q)
            ans[v] = 2;
        return;
    }

    int mid = (l + r) / 2;

    memset(dp[mid - 1], 0, sizeof(dp[mid - 1]));
    dp[mid - 1][v[mid - 1]][v[mid - 1]] = 1;

    memset(pref[mid - 1], 0, sizeof(pref[mid - 1]));
    for (int end = v[mid - 1]; end < K; end++)
        pref[mid - 1][end] = 1;
    for (int i = mid - 2; i >= l; i--) {
        memcpy(dp[i], dp[i + 1], sizeof(dp[i + 1]));
        for (int start = v[i]; start < K; start++) {
            for (int end = start; end < K; end++) {
                    add(dp[i][v[i]][end], dp[i + 1][start][end]);
                }
            }

        dp[i][v[i]][v[i]]++;

        for (int end = 0; end < K; end++) {
            pref[i][end] = 0;
            if (end != 0)
                pref[i][end] = pref[i][end - 1];
            for (int s = 0; s <= end; s++) {
                add(pref[i][end], dp[i][s][end]);
            }
        }
    }

    memset(dp[mid], 0, sizeof(dp[mid]));
    memset(pref[mid], 0, sizeof(pref[mid]));
    pref[mid][v[mid]] = 1;
    dp[mid][v[mid]][v[mid]] = 1;
    for (int i = mid + 1; i < r; i++) {
        memcpy(dp[i], dp[i - 1], sizeof(dp[i -  1]));
        for (int start = 0; start < K; start++) {
            for (int end = start; end <= v[i]; end++) {
                add(dp[i][start][v[i]], dp[i - 1][start][end]);
            }
        }

        dp[i][v[i]][v[i]]++;
        for (int start = 0; start < K; start++) {
            pref[i][start] = 0;
            for (int e = start; e < K; e++) {
                add(pref[i][start], dp[i][start][e]);
            }
        }
    }

    vector<int> q1, q2;
    for (auto v : q) {
        if (queries[v].b <= mid)
            q1.push_back(v);
        else if (queries[v].a >= mid)
            q2.push_back(v);
        else {
            int a = queries[v].a;
            int b = queries[v].b - 1;

            ll res = 0;

            for (int val = 0; val < K; val++) {
                // Subsequences ending at at most val in the right, subsequences ending in exactly val in the left
                res += (ll)(pref[a][val] + 1) * (pref[b][val]);
                res %= MOD;
            }

            ans[v] = res;
            add(ans[v], pref[a][K -1] + 1);
        }
    }

    d_c(l, mid, q1);
    d_c(mid, r, q2);
}

int main(void)
{
    freopen("nondec.in", "r", stdin);
    freopen("nondec.out", "w", stdout);

    scanf("%d %d", &N, &K);

    v.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
        v[i]--;
    }

    scanf("%d", &Q);
    ans.resize(Q);
    for (int i = 0; i < Q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;

        queries.push_back({a, b});
        initial.push_back(i);
    }

    d_c(0, N, initial);

    for (int i = 0; i < Q; i++)
        printf("%d\n", (int)ans[i]);

    return 0;
}