#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

bool revsort(ii a, ii b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first > b.first;
}

struct event {
    int day;
    int cow_id;
    int change;

    event(int d, int cid, int ch) {
        day = d;
        cow_id = cid;
        change = ch;
    }
};
typedef struct event Event;

bool operator < (Event a, Event b)
{
    return a.day < b.day;
}

int n, g;
int maxmilk;
set<ii, decltype(revsort)*> sort_by_milk(revsort);
unordered_map<int, int> production;
vector<Event> events;

int main(void)
{
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    scanf("%d %d", &n, &g);
    int cow, change, day;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &day, &cow, &change);
        events.pb(Event(day, cow, change));
    }
    sort(events.begin(), events.end());
    maxmilk = g;

    int curcow;
    int curchange;
    int total_changes = 0;
    bool changed = false;
    for (auto ev : events) {
        changed = false;
        curcow = ev.cow_id;
        curchange = ev.change;

        if (production.count(curcow) == 0) {
            production[curcow] = g;
            sort_by_milk.insert(mp(g, curcow));
        }

        sort_by_milk.erase(mp(production[curcow], curcow));


        bool isfirst = false;
        bool unique = true;
        if (production[curcow] == maxmilk) isfirst = true;
        if (production[curcow] == maxmilk) {
            // Must not be the unique first for this to be true(and the second to have many less)
            ii secondbest = *(sort_by_milk.begin());
            int secmax = max(secondbest.first, g);

            if (secmax == maxmilk)
                unique = false;

            if (secmax < maxmilk + curchange)
                changed = false;
            else 
                changed = true;
        }
        
        production[curcow] += curchange;
        if (production[curcow] >= maxmilk && (!isfirst || !unique))
            changed = true;

        sort_by_milk.insert(mp(production[curcow], curcow));
        ii maxcow = *(sort_by_milk.begin());
        maxmilk = max(g, maxcow.first);

        if (changed)
            total_changes++;        
    }

    printf("%d\n", total_changes);
}