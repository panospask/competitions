#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K, C;
vector<int> w;

int main(void)
{
    freopen("cauldron.in", "r", stdin);
    freopen("cauldron.out", "w", stdout);

    scanf("%d %d %d", &N, &K, &C);
    
    w.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }
    sort(w.begin(), w.end());

    if (C <= 0) {
        printf("%d\n", K);
        return 0;
    }

    ll ans = K;
    ll potion_sum = 0;
    
    for (int i = 0; i < N && w[i] + potion_sum <= K; i++) {
        ans += C;
    }

    printf("%lld\n", ans);

    return 0;
}