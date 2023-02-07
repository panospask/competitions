#include <bits/stdc++.h>
#define MAXN 100

using namespace std;

typedef pair<int, int> ii;

ii s[MAXN], t[MAXN];
int n;

int main(void)
{
    freopen("blist.in", "r", stdin);
    freopen("blist.out", "w", stdout);

    scanf("%d", &n);
    int bi, si, ti;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &si, &ti, &bi);
        s[i] = make_pair(si, bi);
        t[i] = make_pair(ti, bi);
    }

    sort(s, s + n);
    sort(t, t + n);

    int max_buckets = 0;
    int cur_buckets = 0;
    int curi = 0, curj = 0;

    while (curi < n) {
        if (s[curi].first < t[curj].first) {
            cur_buckets += s[curi].second;
            curi++;
            max_buckets = max(max_buckets, cur_buckets);
        }
        else {
            cur_buckets -= t[curj].second;
            curj++;
        }
    }

    printf("%d\n", max_buckets);
    return 0;
}