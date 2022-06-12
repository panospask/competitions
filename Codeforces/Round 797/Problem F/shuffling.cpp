#include <bits/stdc++.h>
#include <numeric>

using namespace std;

#define pb push_back

int perm[200];
char s[200];
int dp[200];
int goes_to[200];
int n;
bool used[200];

long long int lcm(long long int a, long long int b)
{
    return (a * b) / gcd(a, b);
}

long long int find_path_length(int start, int dest,long long int moves)
{
    if (start == dest)
        return moves;
    
    if (dp[start] != -1)
        return dp[start];

    dp[start] = find_path_length(goes_to[start], dest,moves + 1);
    return dp[start];
}

long long int find_cycle(int a) 
{
    dp[a] = find_path_length(goes_to[a], a, 1);
    return dp[a];
}


long long int calc_i_cycle(int i)
{
    vector<int> cycle;
    cycle.pb(i);
    used[i] = true;

    while (true) {
        int to_push = goes_to[cycle.back()];
        if (!used[to_push]) {
            cycle.pb(to_push);
            used[to_push] = true;
        }
        else 
            break;
    }

    vector<int> new_cyc = cycle;
    for (int j = 1; j < cycle.size(); j++) {
        bool isgood = true;
        for (int k = 0; k < cycle.size() && isgood; k++)
            if (s[cycle[k]] != s[new_cyc[(k + j) % cycle.size()]])
                isgood = false;

        if (isgood)
            return j;
    } 

    return cycle.size();
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d", &n);
        getchar();

        for (int i = 0; i < n; i++) {
            s[i] = getchar();
            dp[i] = -1;
            used[i] = false;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &perm[i]);
            goes_to[perm[i] - 1] = i;
        }

        long long int minmoves = 1;
        for (int i = 0; i < n; i++) {
            if (!used[i])
                minmoves = (long long int) lcm(minmoves, calc_i_cycle(i));
        }

        printf("%lld\n", minmoves);
    }
}