#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> l, r;
vector<int> balls;
set<int> placed;
set<int> avail;

bool sizesort(int a, int b)
{
    if (l[a] == l[b])
        return r[a] - l[a] < r[b] - l[b];

    return l[a] < l[b];
}

bool place(int a)
{
    auto it = avail.lower_bound(l[a]);
    if (it == avail.end()) {
        return false;
    }
    int p = *it;
    if (p > r[a]) {
        return false;
    }

    avail.erase(p);
    placed.insert(p);
    if (placed.find(p + 1) == placed.end())
        avail.insert(p + 1);

    return true;
}

void solve(void)
{
    scanf("%d", &N);

    l.resize(N);
    r.resize(N);
    balls.resize(N);
    avail.clear();
    placed.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l[i], &r[i]);
        balls[i] = i;
        avail.insert(l[i]);
    }

    for (int i = 0; i < N; i++) {
        if (!place(balls[i])) {
            printf("No\n");
            return;
        }
    }

    printf("Yes\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}