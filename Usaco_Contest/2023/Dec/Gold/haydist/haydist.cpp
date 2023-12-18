#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Query {
    int a, b, id;
};
bool operator < (const Query& a, const Query& b)
{
    return (double)a.b / a.a < (double)b.b / b.a;
}

int N, Q;
vector<ll> pref;
vector<ll> suff;
vector<ll> ans;
vector<Query> queries;
vector<int> x;

ll calculate(Query q, int y)
{
    return q.a * pref[y] + q.b * suff[y];
}

int main(void)
{
    scanf("%d", &N);
    pref.resize(N);
    suff.resize(N);
    ans.resize(N);
    x.resize(N);
    queries.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &x[i]);
    sort(x.begin(), x.end());

    pref[0] = 0;
    for (int i = 1; i < N; i++) {
        pref[i] = (ll)i * (x[i] - x[i - 1]) + pref[i - 1];
    }
    suff[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) {
        suff[i] = (ll)(N - 1 - i) * (x[i + 1] - x[i]) + suff[i + 1];
    }

    scanf("%d", &Q);
    for (int q = 0; q < Q; q++) {
        scanf("%d %d", &queries[q].a, &queries[q].b);
        queries[q].id = q;
    }
    sort(queries.begin(), queries.end());

    int cur = 0;
    for (int y = 0; y < N - 1; y++) {
        while (cur < Q && calculate(queries[cur], y) < calculate(queries[cur], y + 1)) {
            ans[queries[cur].id] = calculate(queries[cur], y);
            cur++;
        }
    }
    while (cur < Q) {
        ans[queries[cur].id] = calculate(queries[cur], N - 1);
        cur++;
    }

    for (int i = 0; i < Q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}