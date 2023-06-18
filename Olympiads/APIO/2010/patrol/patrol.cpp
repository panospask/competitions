#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n, k;
vector<vector<int>> adj_list;

vector<int> fully_outside;
vector<int> path_outside;

vector<int> fully_inside;
vector<int> path_inside;
vector<int> second_inside;
vector<int> third_inside;
vector<int> fourth_inside;
vector<int> topkid;
vector<int> seckid;
int len = 0;

void calculate_inside(int node, int par)
{
    fully_inside[node] = path_inside[node] = 0;

    int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    topkid[node] = -1;
    seckid[node] = -1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        calculate_inside(neigh, node);
        fully_inside[node] = max(fully_inside[node], fully_inside[neigh]);

        if (path_inside[neigh] + 1 > p1) {
            seckid[node] = topkid[node];
            topkid[node] = neigh;

            p4 = p3;
            p3 = p2;
            p2 = p1;
            p1 = path_inside[neigh] + 1;
        }
        else if (path_inside[neigh] + 1 > p2) {
            seckid[node] = neigh;

            p4 = p3;
            p3 = p2;
            p2 = path_inside[neigh] + 1;
        }
        else if (path_inside[neigh] + 1 > p3) {
            p4 = p3;
            p3 = path_inside[neigh] + 1;
        }
        else if (path_inside[neigh] + 1 > p4) {
            p4 = path_inside[neigh] + 1;
        }
    }

    fully_inside[node] = max(fully_inside[node], p1 + p2);
    path_inside[node] = p1;
    second_inside[node] = p2;
    third_inside[node] = p3;
    fourth_inside[node] = p4;

}

void calculate_outside(int node, int par)
{
    int f1 = 0, f2 = 0, ch1 = -1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        if (fully_inside[neigh] > f1) {
            ch1 = neigh;

            f2 = f1;
            f1 = fully_inside[neigh];
        }
        else if (fully_inside[neigh] > f2) {
            f2 = fully_inside[neigh];
        }
    }
    for (auto neigh : adj_list[node]) {
        if (neigh == par) continue;

        if (neigh == ch1)
            fully_outside[neigh] = f2;
        else
            fully_outside[neigh] = f1;
    }

    path_outside[node] = 0;
    if (par != -1) {
        if (topkid[par] == node)
            path_outside[node] = second_inside[par];
        else
            path_outside[node] = path_inside[par];

        path_outside[node] = max(path_outside[node], path_outside[par]);
        path_outside[node]++;

        // Find the best full outside path
        fully_outside[node] = max(fully_outside[par], fully_outside[node]);
        int p1, p2;
        if (topkid[par] == node || seckid[par] == node) {
            p2 = max(path_outside[par], third_inside[par]);
            if (topkid[par] == node)
                p1 = second_inside[par];
            else
                p1 = path_inside[par];
        }
        else {
            p1 = path_inside[par];
            p2 = max(path_outside[par], second_inside[par]);
        }

        fully_outside[node] = max(fully_outside[node], p1 + p2);
    }

    len = max(len, fully_inside[node] + fully_outside[node]);
    int add = max(fourth_inside[node], path_outside[node]);
    len = max(len, path_inside[node] + second_inside[node] + third_inside[node] + add);

    for (auto neigh : adj_list[node]) if (neigh != par)
        calculate_outside(neigh, node);

    return;
}

int main(void)
{
    scanf("%d %d", &n, &k);

    adj_list.resize(n);
    fully_inside.resize(n);
    path_inside.resize(n);
    second_inside.resize(n);
    third_inside.resize(n);
    topkid.resize(n);
    path_outside.resize(n);
    fully_outside.assign(n, 0);
    seckid.resize(n);
    fourth_inside.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calculate_inside(0, -1);
    if (k == 1) {
        int ans = 2 * (n - 1) - fully_inside[0] + 1;
        printf("%d\n", ans);
    }
    else {
        calculate_outside(0, -1);
        int ans = 2 * (n - 1) - len + 2;
        printf("%d\n", ans);
    }

    return 0;
}