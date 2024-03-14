#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

vector<int> adj_list[MAXN + 2];

int temp[MAXN + 2];
int dist1[MAXN + 2];
int dist2[MAXN + 2];

int actual_dist[MAXN + 2];

int n;

void dfs(int node, int par, int* arr) 
{
    for (auto kid : adj_list[node]) {
        if (kid != par) {
            arr[kid] = arr[node] + 1;
            dfs(kid, node, arr);
        }
    }
}

int main(void)
{
    scanf("%d", &n);
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    // Arbitrary root to find the first node
    temp[0] = 0; 
    dfs(0, -1, temp);

    int n1 = 0;
    int d1 = 0;
    for (int i = 0; i < n; i++)
        if (temp[i] > d1) {
            n1 = i;
            d1 = temp[i];
        }

    // Now calc dist1
    dist1[n1] = 0;
    dfs(n1, -1, dist1);

    // Now find n1
    int n2 = 0;
    int d2 = -1;
    for (int i = 0; i < n; i++)
        if (dist1[i] > d2) {
            d2 = dist1[i];
            n2 = i;
        }

    // Now calc dist2
    dist2[n2] = 0;
    dfs(n2, -1, dist2);

    for (int i = 0; i < n; i++)
        actual_dist[i] = max(dist1[i], dist2[i]);

    sort(actual_dist, actual_dist + n);
    int curp = 0;
    int components = 1;
    for (int k = 1; k <= n; k++) {
        while (curp < n - 1 && actual_dist[curp] < k) {
            curp++;
            components++;
        }
        

        printf("%d ", components);
    }
    printf("\n");

    return 0;
}