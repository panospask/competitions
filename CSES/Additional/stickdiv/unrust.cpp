#include <bits/stdc++.h>

using namespace std;

int N, X;
multiset<int> lengths;


int main(void)
{
    scanf("%d %d", &X, &N);

    for (int i = 0; i < N; i++) {
        int l;
        scanf("%d", &l);
        lengths.insert(l);
    }

    long long cost = 0;
    while (lengths.size() > 1) {
        int v1 = *lengths.begin();
        lengths.erase(lengths.begin());
        int v2 = *lengths.begin();
        lengths.erase(lengths.begin());

        cost += v1 + v2;
        lengths.insert(v1 + v2);
    }

    printf("%lld\n", cost);
    return 0;
}