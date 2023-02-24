#include <bits/stdc++.h>
#define MAXN 10000

using namespace std;

int n, k;
int ropes[MAXN + 5];

bool can_cut_k_pieces(double length)
{
    int piece_sum = 0;
    for (int i = 0; i < n && piece_sum < k; i++)
        piece_sum += floor(ropes[i] / length);

    return piece_sum >= k;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &ropes[i]);

    double l = 0; // can_cut_k_pieces(l) = true
    double r = 10e8; // can_cut_k_pieces(r) = false

    // 100 iterations are enough for a good persiscion
    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if (can_cut_k_pieces(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lf\n", r);
    return 0;
}