#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20000
#define MAXC 20000

using namespace std;

typedef pair<int, int> ii;

ii cows[MAXN + 5];
multiset<int> chickens;
int n, c;


int main(void)
{
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);

    scanf("%d %d", &c, &n);
    int curchicktime;
    for (int i = 0; i < c; i++) {
        scanf("%d", &curchicktime);
        chickens.insert(curchicktime);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].second, &cows[i].first);
    }
    sort(cows, cows + n);

    int cur_pairs = 0;
    for (int i = 0; i < n; i++) {
        auto it = chickens.lower_bound(cows[i].second);
        if (it != chickens.end() && *it <= cows[i].first) {
            cur_pairs++;
            chickens.erase(it);
        }
    }

    printf("%d\n", cur_pairs);
    return 0;
}