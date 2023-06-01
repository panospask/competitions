#include <bits/stdc++.h>
#define MAXN 20
#define CHECK_BIT(var, pos) (var & (1 << pos))

using namespace std;

int n, m;
// dp[i]: Contains all of the possible remaining sets of banknotes after serving the first i customers 
unordered_set<int> dp[MAXN + 2];

vector<int> accept_by[MAXN + 2];
int notes[MAXN + 2];
int reqs[MAXN + 2];

int calc_sum_by_subset(int s)
{
    int ans = 0;
    for (int i = 0; i < m; i++)
        if (CHECK_BIT(s, i))
            ans += notes[i];

    return ans;
}

void remove(int i, int j)
{
    for (int x = i; x < n; x++)
        reqs[x] = reqs[x + 1];
    n--;

    for (int y = j; y < m - 1; y++)
        notes[y] = notes[y + 1];
    m--;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", &reqs[i]);
    for (int j = 0; j < m; j++)
        scanf("%d", &notes[j]);

    // Purge: If element == requirement it is optimal to remove it
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++) {
            if (i > n || j >= m)
                continue;

            if (reqs[i] == notes[j])
                remove(i, j);
        }

    int start = 0; // No notes used
    dp[0].insert(start);

    // For each customer, calculate all the acceptable sets of notes that would equate to their salary
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < (1<<m); s++) {
            if (calc_sum_by_subset(s) == reqs[i])
                accept_by[i].push_back(s);
        }
    }

    // See if there are any distinct subsets
    for (int i = 1; i <= n; i++) {
        for (auto to_add : accept_by[i])
            for (auto have_used : dp[i-1]) {
                
                // Check if any note is already used
                if ((to_add ^ have_used) != to_add + have_used)
                    continue;

                // Add the current combination of notes
                dp[i].insert(to_add ^ have_used);
            }
    }

    bool ans = !dp[n].empty();
    if (ans)
        printf("YES\n");
    else 
        printf("NO\n");

    return 0;
}