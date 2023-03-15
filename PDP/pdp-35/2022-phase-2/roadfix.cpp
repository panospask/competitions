/* USER: paskalis35pdp
LANG: C++
TASK: roadfix */

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct offer {
    int start;
    int end;
    long long int cost;

    void read_offer(void) {
        int s, l;
        long long int c;
        scanf("%d %d %lld", &s, &l, &c);
        start = s;
        end = s + l;
        cost = c;
    }
};
typedef struct offer Offer;

bool operator < (Offer a, Offer b) 
{
    if (a.end == b.end) {
        if (a.start == b.start)
            return a.cost < b.cost;
        return a.start < b.start;
    }
    return a.end < b.end;
}

int n, m;
vector<Offer> offers;
set<pair<int, long long int>> min_cost_for;

pair<int, int> cur_query;

long long int find_cost_to_reach(int pos) 
{
    if (pos <= cur_query.first)
        return 0;

    pair<int, long long int> t;
    t = make_pair(pos, 0);

    auto i = (min_cost_for.lower_bound(t));
    if (i == min_cost_for.end()) return -1;
    
    t = *i;
    return t.second;
}

int main(void)
{
    // freopen("roadfix.in", "r", stdin);
    // freopen("roadfix.out", "w", stdout);

    scanf("%d %d", &n, &m);
    Offer cur;
    for (int i = 0; i < n; i++) {
        cur.read_offer();
        offers.pb(cur);
    }

    sort(offers.begin(), offers.end());

    for (int q = 0; q < m; q++) {
        min_cost_for.clear();
    
        scanf("%d %d", &cur_query.first, &cur_query.second);
        Offer cur_offer;
        long long int prevcost;
        for (int i = 0; i < n; i++) {
            // Iterate through every offer to calculate the total cost for that offers end

            cur_offer = offers[i];
            if (cur_offer.end <= cur_query.first) continue;
            prevcost = find_cost_to_reach(offers[i].start);
            if (prevcost == -1) continue;

            pair<int, long long int> cur_prog = make_pair(offers[i].end, offers[i].cost + prevcost);
            while (!min_cost_for.empty()) {
                auto p = *min_cost_for.rbegin();
                if (p.second >= cur_prog.second) {
                    // No need to keep p
                    min_cost_for.erase(p);
                }
                else
                    break;
            }
            min_cost_for.insert(cur_prog);
        }

        long long int mincost = LONG_LONG_MAX;
        for (auto possibility : min_cost_for) {
            if (possibility.first >= cur_query.first + cur_query.second)
                mincost = min(mincost, possibility.second);
        }

        if (mincost == LONG_LONG_MAX)
            printf("-1\n");
        else
            printf("%lld\n", mincost);
    }
    return 0;
}