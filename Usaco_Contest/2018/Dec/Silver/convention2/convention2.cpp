#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1e5

using namespace std;

struct cow {
    int arrive;
    int time_taken;
    int seniority;

    void read_cow(int sen) {
        seniority = sen;
        scanf("%d %d", &arrive, &time_taken);
    }
};
typedef struct cow Cow;

bool arrivesort(Cow& a, Cow& b) 
{
    if (a.arrive == b.arrive)
        return a.seniority < b.seniority;
    return a.arrive < b.arrive;
}

bool operator < (const Cow a, const Cow b) 
{
    return a.seniority < b.seniority;
}

int n;
set<Cow> waiting;
vector<Cow> cows;
int time_rem = 0;
int cur_time = 0;    
int arrive_cow = 0;
bool eating = false;
int skip_ahead_by;
int ans = -1;

void make_cow_eat(void)
{
    Cow to_remove = *(waiting.begin());
    time_rem = to_remove.time_taken;
    ans = max(ans, cur_time - to_remove.arrive);
    waiting.erase(to_remove);
    eating = true;
}

int main(void)
{
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    scanf("%d", &n);
    Cow cur;    
    for (int i = 0; i < n; i++) {
        cur.read_cow(i);
        cows.pb(cur);
    }
    sort(cows.begin(), cows.end(), arrivesort);

    while (arrive_cow < n) {
        if (eating && time_rem < cows[arrive_cow].arrive - cur_time) {
            cur_time += time_rem;
            eating = false;
            if (!waiting.empty()) {
                make_cow_eat();
            }
        }
        else {
            skip_ahead_by = cows[arrive_cow].arrive - cur_time;
            if (eating)
                time_rem -= skip_ahead_by;
            cur_time += skip_ahead_by;

            // Enter the cow in the set
            waiting.insert(cows[arrive_cow]);

            if (!eating) {
                make_cow_eat();
            }

            arrive_cow++;
        }
    }

    printf("%d\n", ans);
    return 0;
}