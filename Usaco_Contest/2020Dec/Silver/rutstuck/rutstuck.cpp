#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;
map<ii, int> cowtrans;

struct collide {
    int time;
    int responsible;
    int collidee;
    int resp_time_need;

    collide(ii eastcow, ii northcow) {
        int hortime = northcow.first - eastcow.first;
        int vertime = eastcow.second - northcow.second;

        assert(hortime >= 0 && vertime >= 0 && hortime - vertime != 0);

        if (hortime > vertime) {
            responsible = cowtrans[northcow];
            collidee = cowtrans[eastcow];
        }
        else {
            responsible = cowtrans[eastcow];
            collidee = cowtrans[northcow];
        }

        time = max(hortime, vertime);
        resp_time_need = min(hortime, vertime);
    }
};
typedef struct collide Collide;

vector<ii> eastcows;
vector<ii> northcows;
bool stopped[MAXN];
int stopped_by[MAXN];
vector<int> has_stopped[MAXN];
int counter[MAXN];
int t_s[MAXN];
int n;
int eastnum = 0;
int northnum = 0;
vector<Collide> collisions;

bool operator < (const Collide a, const Collide b) 
{
    return a.time < b.time;
}

void add_counter_to (int cnt, int cow)
{
    counter[cow] += cnt;
    if (stopped_by[cow] != -1)
        add_counter_to(cnt, stopped_by[cow]);
}

int main(void)
{
    // freopen("rutstuck.in", "r", stdin);
    // freopen("rutstuck.out", "w", stdout);

    scanf("%d", &n);
    int x, y;
    char d;
    for (int i = 0; i < n; i++) {
        getchar();
        scanf("%c %d %d", &d, &x, &y);

        if (d == 'E') 
            eastcows.pb(mp(x, y));
        else 
            northcows.pb(mp(x, y));

        cowtrans[mp(x, y)] = i;
        stopped_by[i] = -1;
    }

    for (auto eastcow : eastcows)
        for (auto northcow : northcows) {
            if (eastcow.first >= northcow.first || northcow.second >= eastcow.second)
                continue;

            int hortime = northcow.first - eastcow.first;
            int vertime = eastcow.second - northcow.second;
            if (vertime == hortime)
                continue;

            collisions.pb(Collide(eastcow, northcow));        
        }

    sort (collisions.begin(), collisions.end());

    memset(stopped, false, sizeof(stopped));
    for (auto collision : collisions) {
        if (!stopped[collision.collidee]) {
            if (stopped[collision.responsible] && t_s[collision.responsible] < collision.resp_time_need)
                continue;
            stopped[collision.collidee] = true;
            t_s[collision.collidee] = collision.time;

            stopped_by[collision.collidee] = collision.responsible;
            has_stopped[collision.responsible].pb(collision.collidee);

            add_counter_to(counter[collision.collidee] + 1, collision.responsible);
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", counter[i]);

    return 0;
}