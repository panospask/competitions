#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int x[MAXN + 5];
int v[MAXN + 5];
int n;

bool overlap(double x1, double y1, double x2, double y2)
{
    return x1 <= y2 && x2 <= y1;
}

bool can_meet(double t)
{
    double l_point = -1e9, r_point = 1e9;
    bool isgood = true;
    for (int i = 0; i < n && isgood; i++) {
        double cur_l = x[i] - v[i] * t;
        double cur_r = x[i] + v[i] * t;

        // Perform intersections of two segments
        if (!overlap(l_point, r_point, cur_l, cur_r))
            isgood = false;
        else {
            l_point = max(cur_l, l_point);
            r_point = min(cur_r, r_point);
        }
    }

    return isgood;
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &x[i], &v[i]);

    double l = 0; // can_meet(l) = false
    double r = 1; // can_meet(r) = true
    while (!can_meet(r)) {
        l = r;
        r *= 2;
    }    

    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if (!can_meet(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lf\n", r);
    return 0;
}