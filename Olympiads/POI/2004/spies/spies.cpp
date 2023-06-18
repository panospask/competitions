#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> shadowed_by;
vector<bool> removed;
vector<int> shadows;
queue<int> q;

int total_missions = 0;

void assign_mission(int node)
{
    if (removed[node])
        return;

    shadowed_by[shadows[node]]--;
    removed[node] = true;

    if (!removed[shadows[node]] && shadowed_by[shadows[node]] == 0)
        q.push(shadows[node]);

    total_missions++;
}

int main(void)
{
    scanf("%d", &n);

    removed.assign(n, false);
    shadows.resize(n);
    shadowed_by.resize(n);

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        k--;

        shadows[i] = k;
        shadowed_by[k]++;
    }
    for (int i = 0; i < n; i++) {
        if (shadowed_by[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        removed[v] = true;
        assign_mission(shadows[v]);
    }

    // Now process the cycles
    for (int i = 0; i < n; i++) {
        if (!removed[i]) {
            assert(shadowed_by[i] == 1);

            stack<int> c;
            c.push(i);
            int cur = shadows[i];
            while (cur != i) {
                c.push(cur);
                cur = shadows[cur];
            }

            total_missions += c.size() / 2;
            while (!c.empty()) {
                removed[c.top()] = true;
                c.pop();
            }
        }
    }

    printf("%d\n", total_missions);

    return 0;
}