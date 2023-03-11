#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define MAXT 500

using namespace std;

typedef pair<int, int> ii;

int gain[MAXN + 2];
vector<int> adj_list[MAXN + 2];
int max_money[MAXT + 2][MAXN + 2];
int n, c, m;
int maxgain = 0;

int main(void)
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &c);
    int a, b;
    for (int i = 0; i < n; i++) {
        scanf("%d", &gain[i]);
        maxgain = max(gain[i], maxgain);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        // Reverse the adj_list, you only care about who can reach b, not who a can reach
        adj_list[b].pb(a);
    }

    max_money[0][0] = 0;
    for (int i = 1; i < n; i++)
        max_money[0][i] = -1;

    int total_max = 0;
    cerr << maxgain;
    for (int t = 1; 2 * t * c + 1<= 2 * maxgain; t++) {
        cerr << t << '\n';
        for (int i  = 0; i < n; i++) {
            // Max money for reaching i in t days   
            max_money[t][i] = -1;
            if (max_money[t-1][i] != -1)
                max_money[t][i] = max_money[t-1][i];

            for (auto& neigh : adj_list[i]) {
                if (max_money[t-1][neigh] != -1) 
                    max_money[t][i] = max(max_money[t][i], max_money[t-1][neigh] + gain[i]);
            }
        }

        total_max = max(total_max, max_money[t][0] - c * t * t);
    }

    printf("%d\n", total_max);
    return 0;
}