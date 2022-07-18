/*
ID: panos.p1
LANG: C++11
TASK: maze1
*/

#include <bits/stdc++.h>
#define MAXW 38
#define MAXH 100
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

map<ii, vector<ii>> adj_list;
map<ii, bool> visited;
map<ii, int> dist[2];
ii exit1 = mp(-1, -1), exit2 = mp(-1, -1);
int maxdist = -1;

int w, h;

void set_exit_room(ii room)
{
    if (exit1 == mp(-1, -1))
        exit1 = room;
    else 
        exit2 = room;

    return;
}

void dfs(int test, ii source)
{
    visited.clear();
    queue<ii> q;
    q.push(source);
    visited[source] = true;

    ii cur;
    while (!q.empty()) {
        cur = q.front(); q.pop();

        for (auto& v : adj_list[cur]) {
            if (!visited[v]) {
                dist[test][v] = dist[test][cur] + 1;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main(void)
{
    freopen("maze1.in", "r", stdin);
    freopen("maze1.out", "w", stdout);

    scanf("%d %d", &w, &h);

    char c;
    for (int i = 0; i < 2 * h + 1; i++) {
        getchar();
        for (int j = 0; j < 2 * w + 1; j++) {
            c = getchar();
            if (c == ' ') {
                if (i % 2 == 1 && j % 2 == 1)
                    continue;

                if (i % 2 == 0) {
                    // Wall line: connect north and south
                    // We know that j % 2 == 1 --> room above = [(i / 2) - 1, (j / 2)], room below = [(i / 2), (j / 2)]

                    ii aboveroom = mp(i/ 2 - 1, j / 2);
                    ii belowroom = aboveroom;
                    belowroom.first++;

                    // Check for outings
                    if (aboveroom.first < 0) {
                        set_exit_room(belowroom);
                        continue;
                    }
                    else if (belowroom.first >= h) {
                        set_exit_room(aboveroom);
                        continue;
                    }

                    adj_list[aboveroom].pb(belowroom);
                    adj_list[belowroom].pb(aboveroom);
                }
                else {
                    // Connect east and west

                    ii eastroom = mp(i / 2, j / 2);
                    ii westroom = eastroom;
                    westroom.second--;

                    // Check for outings
                    if (eastroom.second >= w) {
                        set_exit_room(westroom);
                        continue;
                    }
                    else if (westroom.second < 0) {
                        set_exit_room(eastroom);
                        continue;
                    }   


                    adj_list[westroom].pb(eastroom);
                    adj_list[eastroom].pb(westroom);
                }
            }
        }
    }

    dist[0][exit1] = 1;
    dist[1][exit2] = 1;

    dfs(0, exit1);
    dfs(1, exit2);

    ii cur;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            cur = mp(i, j);
            maxdist = max(maxdist, min(dist[0][cur], dist[1][cur]));
        }

    printf("%d\n", maxdist);
    return 0;
}