#include <bits/stdc++.h>
#include "supertrees.h"

#define pb push_back

using namespace std;

int N;
vector<bool> leader;
vector<bool> in_cycle;
vector<vector<int>> members;

vector<int> all_leaders;
vector<vector<int>> b;

int construct(vector<vector<int>> p)
{
    N = p.size();
    leader.assign(N, true);
    in_cycle.assign(N, false);
    members.resize(N);
    b.assign(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (p[i][j] == 3)
                return 0;

    for (int i = 0; i < N; i++) {
        if (!leader[i])
            continue;

        members[i].pb(i);
        all_leaders.pb(i);
        for (int j = 0; j < N; j++) {
            if (i == j || p[i][j] != 1)
                continue;

            if (!leader[j])
                return 0;

            leader[j] = false;
            b[i][j] = b[j][i] = 1;
            members[i].pb(j);
        }

        for (auto m : members[i]) {
            for (int j = 0; j < N; j++)
                if (p[i][j] != p[m][j])
                    return 0;
        }
    }

    // Construct cycles between leaders
    for (auto& l : all_leaders) {
        if (in_cycle[l])
            continue;

        vector<int> cycle;
        int cur = l;
        bool found = true;

        while (found) {
            found = false;
            in_cycle[cur] = true;
            cycle.pb(cur);
            for (auto& j : all_leaders) {
                if (in_cycle[j])
                    continue;

                if (p[cur][j] == 2) {
                    found = true;
                    b[cur][j] = b[j][cur] = 1;
                    cur = j;
                    break;
                }
            }
        }

        if (cycle.back() != l) {
            if (cycle.size() == 2)
                return 0;
            b[cycle.back()][l] = b[l][cycle.back()] = 1;
        }

        for (auto& u : cycle) {
            for (auto& v : cycle) {
                if (u == v)
                    continue;

                if (p[v][u] != 2)
                    return 0;
            }

            for (int v = 0; v < N; v++) {
                if (!leader[v] || in_cycle[v])
                    continue;

                if (p[u][v] == 2)
                    return 0;
            }
        }
    }

    build(b);

    return 1;
}