#include <bits/stdc++.h>
#define MAXN 10000

using namespace std;

int n, k;
int x[MAXN + 5];

// Can you place all k cows with min dist d?
bool can_place_with_dist(int d)
{
    int rem_place = k - 1;
    int latest_placed = x[0];
    for (int i = 1; i < n && rem_place > 0; i++) {
        if (x[i] - latest_placed >= d) {
            latest_placed = x[i];
            rem_place--;
        }
    }

    return rem_place == 0;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);

    int l = 0; // can_place_with_x(l) = true
    int r = 1; // can_place_with_x(r) = false
    while (can_place_with_dist(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_place_with_dist(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%d\n", l);
    return 0;
}