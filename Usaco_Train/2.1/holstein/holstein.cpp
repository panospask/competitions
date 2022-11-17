/*
ID: panos.p1
LANG: C++
TASK: holstein
*/

#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, vector<int>> ii;

struct sit {
    int usenum;
    vector<int> cur_reqs;
    vector<bool> used;
    vector<int> taken;
};

typedef struct sit Sit;

vector<int> cow_reqs;
int v, g;

int vitamins_given[20][30];

map<vector<bool>, bool> tried;

ii bfs(vector<int> reqs)
{
    queue<Sit> q;

    Sit begin;
    begin.cur_reqs = reqs;
    begin.usenum = 0;
    for (int i = 0; i < g; i++)
        begin.used.pb(false);

    q.push(begin);
    while (!q.empty()) {
        Sit cur = q.front(); q.pop();

        bool isgood =  true;
        for (auto& val : cur.cur_reqs)
            if (val > 0) {
                isgood = false;
                break;
            }

        if (isgood)
            return mp(cur.usenum, cur.taken);


        for (int i = 0; i < g; i++) {
            if (!cur.used[i]) {
                cur.used[i] = true;
                if (tried[cur.used]) {
                    cur.used[i] = false;
                    continue;
                }

                for (int j = 0; j < v; j++)
                    cur.cur_reqs[j] -= vitamins_given[i][j];

                cur.taken.pb(i);
                cur.usenum++;
                q.push(cur);
                cur.usenum--;
                tried[cur.used] = true;
                cur.taken.pop_back();

                cur.used[i] = false;
                for (int j = 0; j < v; j++)
                    cur.cur_reqs[j] += vitamins_given[i][j];
            }
        }
    }

    return mp(-1, begin.taken);
}

int main(void)
{
    freopen("holstein.in", "r", stdin);
    freopen("holstein.out", "w", stdout);

    scanf("%d", &v);
    int cur_req;
    for (int i = 0; i < v; i++) {
        scanf("%d", &cur_req);
        cow_reqs.pb(cur_req);
    }

    scanf("%d", &g);
    for (int j = 0; j < g; j++) {
        for (int i = 0; i < v; i++)
            scanf("%d", &vitamins_given[j][i]);
    }

    ii val = bfs(cow_reqs);

    printf("%d", val.first);

    sort (val.second.begin(), val.second.end());

    for (auto& i : val.second)
        printf(" %d", i + 1);

    printf("\n");
    return 0;
}