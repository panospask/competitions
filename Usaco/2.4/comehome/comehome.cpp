/*
ID: panos.p1
LANG: C++11
TASK: comehome
*/

#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<char, int> ci;

map<char, vector<ci>> adj_list;
map<char, int> dist;
set<char> existing;
map<char, bool> used;

int e;

void explore_neighbours(const char node)
{
    int nodedist = dist[node];

    for (auto& neigh : adj_list[node]) {
        dist[neigh.first] = min(dist[neigh.first], nodedist + neigh.second);
    }
}

char find_next_shortest(void)
{
    int mind = INT_MAX;
    char minnode = '\0';

    for (auto node : existing)
        if (!used[node])
            if (dist[node] < mind) {
                mind = dist[node];
                minnode = node;
            }

    return minnode;
}

char find_shortest_to(const char source)
{
    dist[source] = 0;

    explore_neighbours(source);
    used[source] = true;

    char next_shortest = '\0';

    while(next_shortest < 'A' || next_shortest > 'Y') {
        next_shortest = find_next_shortest();

        if (next_shortest >= 'A' && next_shortest <= 'Y')
            return next_shortest;

        explore_neighbours(next_shortest);
        used[next_shortest] = true;
    }

    return '\0';
}

int main(void)
{
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);

    scanf("%d", &e);
    char c1, c2;
    int d;
    for (int i = 0; i < e; i++) {
        getchar();
        scanf("%c %c %d", &c1, &c2, &d);
        adj_list[c1].pb(mp(c2, d));
        adj_list[c2].pb(mp(c1, d));
        dist[c1] = INT_MAX;
        dist[c2] = INT_MAX;
        existing.insert(c1);
        existing.insert(c2);
    }

    char ans = find_shortest_to('Z');
    printf("%c %d\n", ans, dist[ans]);
    return 0;
}