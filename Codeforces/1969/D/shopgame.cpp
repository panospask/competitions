#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Item {
    int a, b;
};

bool operator < (const Item& i, const Item& j)
{
    return i.b < j.b;
}

int N, K;
vector<Item> items;
priority_queue<int> give_free;

ll cur = 0, ans = 0;;

void clear(void)
{
    while (give_free.empty() == false) {
        give_free.pop();
    }
}

void process(int i)
{
    // Move i to the give_free array :)

    if (K && items[i].a < give_free.top()) {
        cur += give_free.top();
        cur -= items[i].a;
        give_free.pop();
        give_free.push(items[i].a);
    }

    // And remove it from the ones bought
    cur -= max(items[i].b - items[i].a, 0);
}

void solve(void)
{
    clear();
    scanf("%d %d", &N, &K);

    items.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &items[i].a);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &items[i].b);
    }

    sort(items.begin(), items.end());
    ans = 0;
    cur = 0;

    for (int i = 0; i < K; i++) {
        give_free.push(items[N - 1 - i].a);
        cur -= items[N - 1 - i].a;
    }
    for (int i = 0; i < N - K; i++) {
        cur += max(items[i].b - items[i].a, 0);
    }

    ans = max(ans, cur);
    for (int i = N - K - 1; i >= 0; i--) {
        process(i);

        ans = max(ans, cur);
    }

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}