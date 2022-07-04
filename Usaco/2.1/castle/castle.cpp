/*
ID: panos.p1
LANG: C++
TASK: castle
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair


using namespace std;
int n, m;

vector<int> adj_list[55 * 55];
bool visited[55 * 55];
long long int room_sz[55 * 55];

int group_rep[55 * 55];

int belong_to[55 * 55];

long long int cur_room_length(int i, int room)
{
    visited[i] = true;
    belong_to[i] = room;

    long long int rl = 1;
    for (auto v : adj_list[i])
        if (!visited[v])
            rl += cur_room_length(v, room);

    return rl;
}

int main(void)
{
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);

    scanf("%d %d", &m, &n);

    int cur_room = 0;
    for (int i = 0; i < n * m; i++) {
        scanf("%d", &cur_room);

        if (!(cur_room & 0b0001)) {
            adj_list[i].pb(i - 1);
        }   
        if (!(cur_room & 0b0010)) {
            adj_list[i].pb(i - m);
        }
        if (!(cur_room & 0b0100)) {
            adj_list[i].pb(i + 1);
        }
        if (!(cur_room & 0b1000)) {
            adj_list[i].pb(i + m);
        }
    }

    long long int max_size = 0;
    int rooms = 0;
    for (int i = 0; i < n * m; i++)
        if (!visited[i]) {
            rooms++;
            long long int sz = cur_room_length(i, rooms - 1);
            room_sz[rooms - 1] = sz;
            max_size = max(max_size, sz);
        }

    pair<int, int> cur_wall_break;
    
    long long int max_with_break = max_size;
    int i;
    for (int j = 0; j < m; j++)    
        for (int k = n - 1; k >= 0; k--) {
            i = k * m + j;




            if (k != 0 && belong_to[i] != belong_to[i - m]) {
                if (room_sz[belong_to[i]] + room_sz[belong_to[i - m]] > max_with_break) {
                    cur_wall_break = mp(i, 1);
                    max_with_break = room_sz[belong_to[i]] + room_sz[belong_to[i - m]];
                }
            }

            if (j != m - 1 && belong_to[i] != belong_to[i + 1]) {
                if (room_sz[belong_to[i]] + room_sz[belong_to[i + 1]] > max_with_break) {
                    cur_wall_break = mp(i, 0);
                    max_with_break = room_sz[belong_to[i]] + room_sz[belong_to[i + 1]];
                }
            }
        }

    printf("%d\n", rooms);
    printf("%lld\n", max_size);
    printf("%lld\n", max_with_break);
    printf("%d %d %c\n", (cur_wall_break.first / m) + 1, (cur_wall_break.first % m) + 1, cur_wall_break.second ? 'N' : 'E');

    return 0;
}