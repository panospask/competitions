#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, K;

vector<int> a, d, f;
int f_pos;

int calc(int v)
{
    return max(abs(a[f_pos] - v), abs(a[f_pos - 1] - v));
}

int check(int t, int d_p, int f_p, int opt)
{
    int v = d[d_p] + f[f_p];

    if (calc(v) < calc(opt))
        return v;
    else
        return opt;
}

void solve(void)
{
    scanf("%d %d %d", &N, &M, &K);

    a.resize(N);
    d.resize(M);
    f.resize(K);

    int first = 0, second = 0;
    f_pos = -1;
    int target;

    scanf("%d", &a[0]);
    for (int i = 1; i < N; i++) {
        scanf("%d", &a[i]);

        if (a[i] - a[i - 1] > first) {
            second = first;
            first = a[i] - a[i - 1];
            f_pos = i;
        }
        else if (a[i] - a[i - 1] > second) {
            second = a[i] - a[i - 1];
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &f[i]);
    }

    sort(d.begin(), d.end());
    sort(f.begin(), f.end());
    target = ((ll)a[f_pos] + a[f_pos - 1]) / 2;

    int f_p = K - 1;
    int opt = d[0] + f[0];
    for (int d_p = 0; d_p < M; d_p++) {
        while (f_p > 0 && f[f_p - 1] + d[d_p] > target) {
            f_p--;
        }

        opt = check(target, d_p, f_p, opt);
        if (f_p > 0)
            opt = check(target, d_p, f_p - 1, opt);
    }


    int ans = max(second, min(first, max(opt - a[f_pos - 1], a[f_pos] - opt)));
    printf("%d\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}