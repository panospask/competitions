#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int A, B, N, M;
vector<int> lines[2];
vector<int> edges[2];

int ptr[2] = {0, 0};
int times[2];

ll ans = 0;

void advance(int cur)
{
    if (ptr[cur] == 0 || ptr[!cur] == 0) {
            ans += (ll)times[cur] * edges[cur][ptr[cur]];
        }
        else {
            ans += (ll)((times[cur]) - ptr[!cur] + 1) * edges[cur][ptr[cur]];
        }

    ptr[cur]++;
}

int main(void)
{
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    scanf("%d %d %d %d", &A, &B, &N, &M);

    times[0] = M; times[1] = N;
    edges[0].resize(N + 1);
    edges[1].resize(M + 1);
    lines[0].resize(N);
    lines[1].resize(M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &lines[0][i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &lines[1][i]);
    }

    sort(lines[0].begin(), lines[0].end());
    int prv = 0;
    for (int i = 0; i < N; i++) {
        edges[0][i] = lines[0][i] - prv;

        prv = lines[0][i];
    }
    edges[0][N] = A - prv;

    sort(lines[1].begin(), lines[1].end());
    prv = 0;
    for (int i = 0; i < M; i++) {
        edges[1][i] = lines[1][i] - prv;
        
        prv = lines[1][i];
    }
    edges[1][M] = B - prv;

    sort(edges[0].begin(), edges[0].end());
    sort(edges[1].begin(), edges[1].end());

    ans = 0;
    while (ptr[0] <= N && ptr[1] <= M) {
        int cur = 0;
        if (edges[0][ptr[0]] >= edges[1][ptr[1]]) {
            cur = 1;
        }

        advance(cur);
    }
    while (ptr[0] <= N) {
        advance(0);
    }
    while (ptr[1] <= M) {
        advance(1);
    }

    printf("%lld\n", ans);

    return 0;
}