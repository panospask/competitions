#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> p;
vector<int> q;
vector<bool> visited;

// cycles of the permutation arranged by length
vector<vector<int>> cycles;

int main(void)
{
    scanf("%d", &N);

    p.resize(N);
    q.assign(N, -1);
    visited.assign(N, false);
    cycles.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            // New cycle

            vector<int> c = {i};
            visited[i] = true;            
            for (int v = p[i]; v != i; v = p[v]) {
                c.pb(v);
                visited[v] = true;
            }

            if (c.size() % 2) {
                // Cycle has odd size, can be passed alone to q
                int half = c.size() / 2;
                for (int i = 0; i < half; i++) {
                    q[c[i]] = c[i + half + 1];
                    q[c[i + half + 1]] = c[i + 1];
                }
                q[c[half]] = c[0];
            }
            else {
                // Cycle has even size, cannot be passed alone to q
                if (cycles[c.size() - 1].empty()) {
                    cycles[c.size() - 1] = c;
                }
                else {
                    auto d = cycles[c.size() - 1];
                    cycles[c.size() - 1].clear();

                    // Merge c and d
                    for (int i = 0; i < c.size(); i++) {
                        q[c[i]] = d[i];
                        q[d[i]] = c[(i + 1) % c.size()];
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (q[i] == -1) {
            printf("-1\n");
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", q[i] + 1);
    }
    printf("\n");

    return 0;
}