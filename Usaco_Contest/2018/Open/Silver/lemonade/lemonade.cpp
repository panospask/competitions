#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n;
multiset<int> cows;
int cur_waiting;

int main(void)
{
    freopen("lemonade.in", "r", stdin);
    freopen("lemonade.out", "w", stdout);

    scanf("%d", &n);
    int curcow;
    for (int i = 0; i < n; i++) {
        scanf("%d", &curcow);
        cows.insert(curcow);
    }

    cur_waiting = 0;
    while (!cows.empty()) {
        auto it = cows.lower_bound(cur_waiting);
        if (it == cows.begin()) {
            cur_waiting++;
            it = cows.end();
            cows.erase(--it);
        }
        else 
            cows.erase(--it);
    }

    printf("%d\n", cur_waiting);
    return 0;
}