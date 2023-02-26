#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 10000

using namespace std;

multiset<int> finish_at;

int n, t;
int d[MAXN + 5];

bool will_finish(int k)
{
    finish_at.clear();
    int cur_time = 0;
    for (int i = 0; i < k; i++) 
        finish_at.insert(d[i]);
    int cur_cow = k;
    while (cur_cow < n && cur_time <= t) {
        cur_time = *(finish_at.begin());
        finish_at.erase(finish_at.begin());
        finish_at.insert(cur_time + d[cur_cow]);
        cur_cow++;
    }

    auto it = finish_at.end();
    cur_time = *--it;
    return cur_time <= t;
}

int main(void)
{
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; i++) 
        scanf("%d", &d[i]);

    int l = 0; //will_finish(l) = false
    int r = n; //will_finish(r) = true
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (!will_finish(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%d\n", r);
    return 0;
}