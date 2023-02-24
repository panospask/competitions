#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

ii a[MAXN + 5];
pair<double, double> tmp[MAXN + 5];
int n, k;

bool diffsort(pair<double, double>& a, pair<double, double>& b)
{
    return a.first - a.second > b.first - b.second;
}

bool can_make_equation(double x)
{
    for (int i = 0; i < n; i++) {
        tmp[i] = make_pair((double)a[i].first, a[i].second * x);
    }
    sort(tmp, tmp + n, diffsort);

    double s = 0;
    for (int i = 0; i < k; i++)
        s += tmp[i].first - tmp[i].second;

    return s >= 0;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &a[i].first, &a[i].second);

    double l = 0; // can_make_equation(l) = true
    double r  = 1e5; // can_make_equation(r) = false
    for (int i = 0; i < 40; i++) {
        double mid = (l + r) / 2;
        if (can_make_equation(mid))
            l = mid;
        else    
            r = mid;
    }

    printf("%.10lf\n", l);
    return 0;
}