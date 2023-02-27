#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

struct spot {
    long long int x, y;
    long long int time;

    void read_spot(void) {
        scanf("%lld %lld %lld", &x, &y, &time);
    }
};
typedef struct spot Spot;

bool operator < (const Spot& a, const Spot& b)
{
    return a.time < b.time;
}

multiset<Spot> events;
vector<Spot> allibies;
int n, g;

bool can_make_on_time(Spot& a, Spot& b)
{
    long long int dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);

    return dist <= (a.time - b.time) * (a.time - b.time);
}

int main(void)
{
    // freopen("cowlibi.in", "r", stdin);
    // freopen("cowlibi.out", "w", stdout);

    scanf("%d %d", &g, &n);
    Spot cur;
    for (int i = 0; i < g; i++) {
        cur.read_spot();
        events.insert(cur);
    }

    allibies.resize(n);
    for (int i = 0; i < n; i++)
        allibies[i].read_spot();

    int innocent_cows = 0;
    for (auto a : allibies) {
        bool innocent = false;
        auto it = events.lower_bound(a);
        if (it != events.end()) {
            Spot after = *it;
            if (!can_make_on_time(a, after))
                innocent = true;
        }
        if (it != events.begin()) {
            Spot bef = *--it;
            if (!can_make_on_time(a, bef))
                innocent = true;
        }

        innocent_cows += innocent;
    }

    printf("%d\n", innocent_cows);
}