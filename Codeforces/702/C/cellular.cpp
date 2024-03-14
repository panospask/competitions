#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> a;
vector<int> b;

vector<int> before, after;

int main(void)
{
    scanf("%d %d", &M, &N);

    a.resize(N);
    b.resize(M);
    after.assign(M, INT_MAX);
    before.assign(M, INT_MAX);

    for (int i = 0; i < M; i++)
        scanf("%d", &b[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int p = 0;
    for (int i = 0; i < N; i++) {
        while (p != M && b[p] <= a[i]) {
            after[p] = a[i] - b[p];
            p++;
        }
    }
    p = M - 1;
    for (int i = N - 1; i >= 0; i--) {
        while (p >= 0 && b[p] > a[i]) {
            before[p] = b[p] - a[i];
            p--;
        }
    }

    int ans = 0;
    for (int j = 0; j < M; j++) {
        ans = max(ans, min(before[j], after[j]));
    }

    printf("%d\n", ans);
}