#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> a;

int ask(int i, int j, bool orq)
{
    i++; j++;

    if (orq) {
        printf("or");
    }
    else {
        printf("and");
    }

    printf(" %d %d\n", i, j);
    fflush(stdout);

    int ans;
    scanf("%d", &ans);
    return ans;
}

int calcsum(int orval, int andval)
{
    int xorval = (~andval) &  orval;

    return xorval + 2 * andval;
}

int main(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);

    int r1 = calcsum(ask(0, 1, true), ask(0, 1, false));
    int r2 = calcsum(ask(1, 2, true), ask(1, 2, false));
    int r3 = calcsum(ask(0, 2, true), ask(0, 2, false));

    a[0] = (r1 + r3 - r2) / 2;
    a[1] = r1 - a[0];
    a[2] = r3 - a[0];

    for (int i = 3; i < N; i++) {
        a[i] = calcsum(ask(0, i, true), ask(0, i, false)) - a[0];
    }

    sort(a.begin(), a.end());

    printf("finish %d\n", a[K - 1]);

    return 0;
}