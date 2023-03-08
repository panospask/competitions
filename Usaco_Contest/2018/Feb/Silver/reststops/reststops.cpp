#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

struct restpoint {
    int x;
    int c;

};
typedef struct restpoint RestPoint;

bool operator < (RestPoint& a, RestPoint& b) {
    if (b.c == a.c)
        return a.x < b.x;
    return a.c > b.c;
}

int l, n, r_f, r_b;
RestPoint points[MAXN + 2];

int main(void)
{
    freopen("reststops.in", "r", stdin);
    freopen("reststops.out", "w", stdout);

    scanf("%d %d %d %d", &l, &n, &r_f, &r_b);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].c);
    }
    sort(points, points + n);

    int cur_point = 0;
    int prev_location = 0;
    long long int ans = 0;
    while (cur_point < n) {
        long long int time_taken_bessie = (long long int)r_b * abs(points[cur_point].x - prev_location);
        long long int time_taken_fj = (long long int)r_f * abs(points[cur_point].x - prev_location);

        ans += points[cur_point].c * abs(time_taken_bessie - time_taken_fj);

        prev_location = points[cur_point].x;
        int i = cur_point + 1;
        while (i < n && points[i].x <= points[cur_point].x)
            i++;
        cur_point = i;
    }

    printf("%lld\n", ans);
    return 0;
}