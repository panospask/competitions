#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
#define mp make_pair
#define pb push_back

ii lefts[100000];
ii rights[100000];
// vector<int> neigh[100000];
vector<vector<int>> neigh;
vector<bool> color;
vector<bool> used;
int n;

void dfs(int i)
{
    used[i] = true;

    for (auto j : neigh[i]) {
        if (!used[j])
            dfs(j);
    }   
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d", &n);


        used.clear();
        used.resize(n);
        color.resize(n);
        neigh.clear();
        neigh.resize(n);
        int scan;
        for (int i = 0; i < n; i++) {
            scanf("%d", &scan);
            color[i] = (bool) scan;
            scanf("%d", &lefts[i].first);
            scanf("%d", &rights[i].first);
            lefts[i].second = i;
            rights[i].second = i;
            neigh[i].clear();
        }

        sort(lefts, lefts + n);
        sort(rights, rights + n);

        set<int> running;
        int l = 0, r = 0;
        while (l < n || r < n) {
            if (r == n || (l != n && lefts[l].first <= rights[r].first)) {
                int cur = lefts[l].second;
                int col = color[cur];

                for (auto x : running) {
                    if (color[x] != col) {
                        neigh[x].pb(cur);
                        neigh[cur].pb(x);
                    }
                }

                running.insert(cur);
                l++;
            }
            else {
                int cur = rights[r].second;
                running.erase(cur);
                r++;
            }
        }

        int num = 0;
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                dfs(i);
                num++;
            }
        }

        printf("%d\n", num);
    }

    return 0;
}