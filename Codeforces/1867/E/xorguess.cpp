#include <stdio.h>

using namespace std;

int N, K;

void print(int i, bool ans)
{
    printf("%c %d\n", ans ? '!' : '?', i + !ans);
    fflush(stdout);
}

int get(void)
{
    int num;
    scanf("%d", &num);

    return num;
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    int res = 0;
    int extra = N % K;

    if (extra) {

        print(0, false);
        res ^= get();

        print(extra / 2, false);
        res ^= get();
    }

    for (int i = extra; i < N; i += K) {
        print(i, false);
        res ^= get();
    }

    print(res, true);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}