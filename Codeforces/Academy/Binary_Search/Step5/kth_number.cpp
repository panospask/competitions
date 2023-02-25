#include <bits/stdc++.h>
#define MAXN 50

using namespace std;

typedef pair<int, int> ii;

ii segments[MAXN + 5];
int n, k;

long long int count_before_or_eq(int x)
{
    long long int total = 0;
    for (int i = 0; i < n; i++) {
        if (segments[i].first > x) continue;

        total += (long long int) min(segments[i].second, x) - segments[i].first + 1;
    }

    return total;
}

bool is_before_k(int x)
{
    if (count_before_or_eq(x) < k)
        return true;
    else 
        return false;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    k++;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segments[i].first, &segments[i].second);
    }

    int l = INT_MIN; // is_before_k(l) = true
    int r = INT_MAX; // is_before_k(r) = false
    while (r > l + 1) {
        int mid = ((long long int) l + r) / 2;
        if (is_before_k(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%d\n", r);
    return 0;
}