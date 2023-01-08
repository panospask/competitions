#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, k;
vector<int> kids[MAXN];
int time_taken[MAXN];
int father[MAXN];
int max_time_taken[MAXN];
set<int> kidsless;

int calc_time_taken(int node)
{
    if (kidsless.find(node) == kidsless.end()) {
        max_time_taken[node] = time_taken[node];
        return max_time_taken[node];
    }

    max_time_taken[node] = 0;
    for (auto& kid : kids[node]) 
        max_time_taken[node] = max(max_time_taken[node], calc_time_taken(kid));

    max_time_taken[node] += time_taken[node];
    return max_time_taken[node];
}

int main(void)
{
    freopen("filiki.in", "r", stdin);
    freopen("filiki.out", "w", stdout);

    scanf("%d %d", &n, &k);
    time_taken[0] = 0;
    father[0] = 0;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &father[i], &time_taken[i]);
        father[i]--;
        time_taken[i]--;
        kidsless.erase(father[i]);
        kidsless.insert(i);
    }


}