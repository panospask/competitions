#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

struct Cube {
    int x, y, z;
};

bool operator < (Cube a, Cube b)
{
    return make_tuple(a.x, a.y, a.z) < make_tuple(b.x, b.y, b.z);
}

int N, M, H;

vector<Cube> ans;

vector<vector<int>> y;
vector<vector<int>> z;

void fail(void)
{
    printf("-1\n");
    exit(0);
}

void maximize(int x, vector<int> y, vector<int> z)
{
    for (auto y1 : y) {
        for (auto z1 : z){
            ans.pb({x, y1, z1});
        }
    }
}

void minimize(int x, vector<int> y, vector<int> z)
{
    vector<pi> res;

    bool s = false;
    if (y.size() > z.size()) {
        swap(y, z);
        s = true;
    }

    while (y.size() < z.size()) {
        y.pb(y.front());
    }
    sort(y.begin(), y.end());

    for (int i = 0; i < y.size(); i++) {
        res.pb({y[i], z[i]});
        if (s) {
            swap(res[i].first, res[i].second);
        }

        ans.pb({x, res[i].first, res[i].second});
    }
}

void print_answer(void)
{
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());

    for (auto [i, j, k] : ans) {
        printf("%d %d %d\n", i, j, k);
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &H);

    y.resize(N);
    z.resize(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v;
            scanf("%1d", &v);

            if (v) {
                y[i].pb(j);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < H; j++) {
            int v;
            scanf("%1d", &v);

            if (v) {
                z[i].pb(j);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (y[i].size() && !z[i].size()) {
            fail();
        }
        if (z[i].size() && !y[i].size()) {
            fail();
        }

        maximize(i, y[i], z[i]);
    }

    print_answer();
    ans.clear();

    for (int i = 0; i < N; i++) {
        minimize(i, y[i], z[i]);
    }
    print_answer();

    return 0;
}