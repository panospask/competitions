#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, d;
int a[MAXN + 5];
double pref_sum[MAXN + 5];
double min_of_prefsum[MAXN + 5];
int min_pos[MAXN + 5];
pair<int, int> indices;

bool can_have_avg(double x)
{
    pref_sum[0] = 0;
    min_of_prefsum[0] = 0;
    min_pos[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + a[i-1] - x;
        if (pref_sum[i] < min_of_prefsum[i - 1]) {
            min_of_prefsum[i] = pref_sum[i];
            min_pos[i] = i;
        }
        else {
            min_of_prefsum[i] = min_of_prefsum[i - 1];
            min_pos[i] = min_pos[i - 1];
        }
    }

    bool found = false;
    for (int i = d; i <= n && !found; i++) 
        if (pref_sum[i] >= min_of_prefsum[i - d]) {
            found = true;
            indices = make_pair(min_pos[i - d] + 1, i);
        }

    return found;
}

int main(void)
{
    scanf("%d %d", &n, &d);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    double  l = 0; //can_have_avg(l) = true
    double r = 101; //can_have_avg(r) = false
    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if (can_have_avg(mid))
            l = mid;
        else 
            r = mid;
    }

    can_have_avg(l);
    printf("%d %d\n", indices.first, indices.second);
    return 0;
}