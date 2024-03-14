#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> s;

int main(void)
{
    scanf("%d %d", &N, &M);

    s.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }

    for (int i = 1; i < N; i++) {
        s[i] = max(s[i], s[i - 1] - M);
    }
    for (int i = N - 2; i >= 0; i--) {
        s[i] = max(s[i], s[i + 1] - M);
    }

    for (int i = 0; i < N; i++)
        printf("%d ", s[i]);
    printf("\n");

    return 0;
}