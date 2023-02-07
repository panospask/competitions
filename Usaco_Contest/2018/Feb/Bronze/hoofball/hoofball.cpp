#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

typedef pair<int, int> ii;

set<ii> playalonepairs;
int x[MAXN];
int throw_to[MAXN];
int n;

bool has_at(int cow, int dir)
{
    int to_test = cow + dir;

    if (to_test >= 0 && to_test < n) {
        if (throw_to[to_test] == cow)
            return true;
    }

    return false;
}

int give_balls_to_pair(ii cowspots)
{
    return max(has_at(cowspots.second, -1) + has_at(cowspots.first, +1), 1);
}

int main(void)
{
    freopen("hoofball.in", "r", stdin);
    freopen("hoofball.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) { 
        scanf("%d", &x[i]);
    }

    sort(x, x + n);

    throw_to[0] = 1;
    int dist1, dist2;
    for (int i = 1; i < n - 1; i++) {
        dist1 = abs(x[i-1] - x[i]);
        dist2 = abs(x[i] - x[i+1]);

        if (dist1 <= dist2) {
            throw_to[i] = i - 1;
            if (throw_to[i - 1] == i)
                playalonepairs.insert(mp(i, i -1));
        }
        else {
            throw_to[i] = i + 1;
        }
    }
    throw_to[n - 1] = n - 2;
    if (throw_to[n - 2] == n - 1)
        playalonepairs.insert(mp(n - 1, n - 2));


    int ans = 0;
    for (auto& p : playalonepairs)  
        ans += give_balls_to_pair(p);

    printf("%d\n", ans);
    return 0;
}