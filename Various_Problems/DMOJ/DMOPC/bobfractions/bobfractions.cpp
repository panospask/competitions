#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<vector<ll>> Matrix;

const int MOD = (int)1e9 + 7;

Matrix multiply(const Matrix a, const Matrix b)
{
    Matrix c;
    c.resize(a.size(), vector<ll>(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int p = 0; p < a.size(); p++) {
                c[i][j] += a[i][p] * b[p][j];
                c[i][j] %= MOD;
            }
        }
    }

    return c;
}


int n, q;
vector<int> v;
vector<pair<pair<int, int>, int>> queries;
vector<Matrix> ans;
vector<Matrix> cur;

vector<pi> unsorted;

void d_c(int l, int r, vector<int>& q)
{
    if (l == r - 1) {
        for (auto i : q) {
            ans[queries[i].second] = {{v[l], 1}, {1, 0}};
        }

        return;
    }

    int mid = (l + r) / 2;

    cur[mid - 1] = {{v[mid - 1], 1}, {1, 0}};
    for (int i = mid - 2; i >= l; i--)
        cur[i] = multiply({{v[i], 1}, {1, 0}}, cur[i + 1]);

    cur[mid] = {{v[mid], 1}, {1, 0}};
    for (int i = mid + 1; i < r; i++) {
        cur[i] = multiply(cur[i - 1], {{v[i], 1}, {1, 0}});
    }

    vector<int> q1, q2;

    for (auto v : q) {
        if (queries[v].first.second <= mid) {
            q1.push_back(v);
        }
        else if (queries[v].first.first >= mid) {
            q2.push_back(v);
        }
        else {
            int a = queries[v].first.first;
            int b = queries[v].first.second - 1;

            ans[queries[v].second] = multiply(cur[a], cur[b]);
        }
    }

    d_c(l, mid, q1);
    d_c(mid, r, q2);
}

int main(void)
{
    scanf("%d %d", &n, &q);

    v.resize(n);
    cur.resize(n);
    ans.resize(q);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    int i = 0;
    vector<int> initial;
    while (q--) {
        int l, b;
        scanf("%d %d", &l, &b);
        l--;
        b--;

        initial.push_back(i);
        queries.push_back(mp(mp(l, b), i));
        unsorted.push_back(mp(l, b));
        i++;
    }
    sort(queries.begin(), queries.end(), [] (pair<pi, int>& a, pair<pi, int>& b)
                                 {return mp(a.first.second, a.first.first) < mp(b.first.second, b.first.first);});

    d_c(0, n, initial);

    for (int i = 0; i < queries.size(); i++) {
        if (unsorted[i].first == unsorted[i].second) {
            printf("%d 1\n", v[unsorted[i].first]);
        }
        else {
            // mul by r
            int r = unsorted[i].second;
            ll nom = (ans[i][0][0] * v[r]) % MOD + (ans[i][0][1]);
            ll den = (ans[i][1][0] * v[r]) % MOD + (ans[i][1][1]);
            nom %= MOD;
            den %= MOD;

            printf("%lld %lld\n", nom, den);
        }
    }
}