#include <bits/stdc++.h>
#define MAXN 2000000

using namespace std;

int n, x;
multiset<int> piece_sizes;

int main(void)
{
    scanf("%d %d", &x, &n);
    int cur_size;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cur_size);
        piece_sizes.insert(cur_size);
    }

    long long int ttl_cost = 0;
    while (piece_sizes.size() > 1) {
        auto it = piece_sizes.begin();
        int a = *it;
        piece_sizes.erase(it);
        it = piece_sizes.begin();
        int b = *it;
        piece_sizes.erase(it);

        piece_sizes.insert(a + b);
        ttl_cost += a + b;
    }

    printf("%lld\n", ttl_cost);
    return 0;
}