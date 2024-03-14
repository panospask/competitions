#include <bits/stdc++.h>
#define MAXN 60000

using namespace std;

int x[MAXN + 5];
int v[MAXN + 5];
int n;

bool intersect(double a1, double b1, double a2, double b2)
{
    return a1 <= b2 && a2 <= b1;
}

bool can_meet_at(double t)
{
    double ttl_segment_start = 0;
    double ttl_segment_end = INFINITY;
    bool isgood = true;
    double curseg_start, curseg_end;
    for (int seg = 0; seg < n && isgood; seg++) {
        curseg_start = x[seg] - v[seg] * t;
        curseg_end = x[seg] + v[seg] * t;

        if (!intersect(ttl_segment_start, ttl_segment_end, curseg_start, curseg_end))
            isgood = false;
        else {
            ttl_segment_start = max(ttl_segment_start, curseg_start);
            ttl_segment_end = min(ttl_segment_end, curseg_end);
        }
    }

    return isgood;
}

int main(void)
{
    scanf("%d", &n);
    int maxx = 0;
    for (int i = 0; i < n; i++) { 
        scanf("%d", &x[i]);
        maxx = max(maxx, x[i]);
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    double l = 0; //can_meet_at(l) = false
    double r = maxx; //can_meet_at(r) = true
    for (int i = 0; i < 70; i++) {
        auto mid = (l + r) / 2;
        if (can_meet_at(mid))
            r = mid;
        else 
            l = mid;
    }

    printf("%.10lf\n", r);
    return 0;
}