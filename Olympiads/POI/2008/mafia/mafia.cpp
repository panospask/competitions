#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> target;
vector<bool> visited;
vector<int> targeted_by;
queue<int> q;

// Maximum variables
vector<bool> dead;

// Minimum variables


int calcmax(void)
{
    targeted_by.assign(n, false);
    visited.assign(n, false);
    dead.assign(n, false);

    for (int i = 0; i < n; i++) {
        targeted_by[target[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (targeted_by[i] == 0)
            q.push(i);
    }

    int ans = 0;

    // Process the shootings in reverse order
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        visited[cur] = true;

        dead[target[cur]] = true;
        targeted_by[target[cur]]--;
        if (targeted_by[target[cur]] == 0)
            q.push(target[cur]);
    }
    for (int i = 0; i < n; i++)
        ans += (visited[i] && dead[i]);

    // Now the cycles(They will begin first)
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            stack<int> cycle;
            cycle.push(i);

            bool outside = dead[i];

            int cur = target[i];
            while (cur != i) {
                cycle.push(cur);
                outside = outside || dead[cur];
                cur = target[cur];
            }

            if (outside)
                ans += cycle.size();
            else
                ans += max(1, (int)cycle.size() - 1);

            while (!cycle.empty()) {
                visited[cycle.top()] = true;
                cycle.pop();
            }
        }
    }

    return ans;
}

int shoot(int node)
{
    if (visited[node])
        return false;

    visited[node] = true;

    targeted_by[target[node]]--;
    if (!visited[target[node]] && targeted_by[target[node]] == 0) {
        // No one can, or has, shot the node's target
        // Therefore the target will shoot the next person
        q.push(target[node]);
    }

    return true;
}

int calcmin(void)
{
    targeted_by.assign(n, false);
    visited.assign(n, false);

    for (int i = 0; i < n; i++) {
        targeted_by[target[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (targeted_by[i] == 0)
            q.push(i);
    }

    int ans = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        // Current node has no one pointing at it => Must necessarily point to it's destination
        visited[cur] = true;
        ans += shoot(target[cur]);
    }

    // Now deal with cycles
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            stack<int> s;
            s.push(i);

            int cur = target[i];
            while (cur != i) {
                s.push(cur);
                cur = target[cur];
            }

            int total = s.size();

            // It's ceil(total / 2) not floor..
            ans += total / 2 + total % 2;

            while (!s.empty()) {
                visited[s.top()] = true;
                s.pop();
            }
        }
    }

    return ans;
}

int main(void)
{
    scanf("%d", &n);

    target.resize(n);

    for (int i = 0; i < n; i++) {
        int s;
        scanf("%d", &s);
        s--;

        target[i] = s;
    }

    printf("%d %d\n", calcmin(), calcmax());
}