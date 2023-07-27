#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> a;
vector<bool> wins;

int main(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    wins.resize(K + 1);
    wins[0] = false;
    for (int i = 1; i <= K; i++) {
        wins[i] = false;
        for (int j = 0; j < N; j++) {
            if (i - a[j] >= 0 && !wins[i - a[j]])
                wins[i] = true;
        }
    }

    if (wins[K])
        printf("First\n");
    else
        printf("Second\n");

    return 0;
}