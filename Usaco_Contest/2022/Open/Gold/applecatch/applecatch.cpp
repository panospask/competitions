#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct Event {
    int x;
    int t;
    int n;
};
struct LeftSort {
    int i;
};
struct RightSort {
    int i;
};

// To be used in the set
bool operator < (const Event& a, const Event& b)
{
    return a.x - a.t < b.x - b.t;
}

int N;
vector<Event> cows;
vector<Event> apples;
multiset<Event> active;

// Comparator to be used in initial sorting
bool cmp(const Event& a, const Event& b)
{
    return a.x + a.t < b.x + b.t;
}

int main(void)
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int q, t, x, n;
        scanf("%d %d %d %d", &q, &t, &x, &n);
        Event cur = {x, t, n};
        if (q == 1) {
            cows.pb(cur);
        }
        else {
            apples.pb(cur);
        }
    }

    sort(cows.begin(), cows.end(), cmp);
    sort(apples.begin(), apples.end(), cmp);

    int ans = 0;
    int c_p = 0;
    for (int i = 0; i < apples.size(); i++) {
        Event cur_apple = apples[i];

        while (c_p < cows.size() && !cmp(apples[i], cows[c_p])) {
            active.insert(cows[c_p]);
            c_p++;
        }

        // Choose the cow set that can go the least right
        auto it = active.lower_bound(cur_apple);
        while (cur_apple.n > 0 && it != active.end()) {
            Event cur_cow = *it;
            active.erase(it);

            int rm = min(cur_apple.n, cur_cow.n);
            cur_apple.n -= rm;
            cur_cow.n -= rm;
            ans += rm;

            if (cur_cow.n > 0) {
                active.insert(cur_cow);
            }

            it = active.lower_bound(cur_apple);
        }
    }

    printf("%d\n", ans);

    return 0;
}