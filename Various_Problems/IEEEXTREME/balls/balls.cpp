#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;
int K;
vector<int> E;

ll ans = 0;

void brute(int pos, int use, ll prod)
{
    if (prod > N) {
        return;
    }

    if (pos == K) {
        int s = use % 2 ? 1 : -1;
        ans += s * N / prod;

        return;
    }

    brute(pos + 1, use + 1, prod * E[pos]);
    brute(pos + 1, use, prod);
}

int main(void)
{
    scanf("%lld %d", &N, &K);

    E.resize(K);
    for (int i = 0; i < K; i++) {
        scanf("%d", &E[i]);
    }

    ans = 0;
    brute(0, 0, 1);
    ans += N;

    printf("%lld\n", ans);

    return 0;
}