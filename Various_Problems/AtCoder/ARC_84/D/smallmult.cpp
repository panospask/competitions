#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> d;
vector<bool> vis;

int main(void)
{
    scanf("%d", &n);

    d.assign(n, INT_MAX);
    vis.assign(n, false);
    d[1] = 1;
    deque<int> q;
    q.push_back(1);

    int ans = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        if (vis[cur])
            continue;

        vis[cur] = true;

        if (cur == 0) {
            ans = d[cur];
            break;
        }

        int nxt = cur * 10 % n;
        if (d[nxt] > d[cur]) {
            d[nxt] = d[cur];
            q.push_front(nxt);
        }

        nxt = (cur + 1) % n;
        if (d[nxt] > d[cur] + 1) {
            d[nxt] = d[cur] + 1;
            q.push_back(nxt);
        }


    }

    printf("%d\n", ans);
    return 0;
}