#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> a, srt;

void solve(void)
{
    scanf("%d %d", &N, &M);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    srt = a;
    sort(srt.begin(), srt.end());

    int wins = 0;
    while (srt[wins] <= M && wins < N) {
        M -= srt[wins];
        wins++;
    }

    int pos = max(N - wins, 1);
    int v = M;
    if (wins) {
        v += srt[wins - 1];
    }
    if (a[N - pos] > v) {
        pos++;
    }

    printf("%d\n", pos);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}