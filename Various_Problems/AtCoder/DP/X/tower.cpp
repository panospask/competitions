#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAXV = 1e4;

struct Block {
    int w, st, v;
    bool operator < (const Block& b) {
        return this->st + this->w < b.st + b.w;
    }
};

int N;
ll dp[MAXV + 1];
vector<Block> blocks;

int main(void)
{
    scanf("%d", &N);

    blocks.resize(N);
    for (int i = 0; i < N; i++)
        scanf("%d %d %d", &blocks[i].w, &blocks[i].st, &blocks[i].v);
    sort(blocks.begin(), blocks.end());

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = blocks[i].st; j >= 0; j--) {
            ll v = dp[j] + blocks[i].v;
            ll w = j + blocks[i].w;

            ans = max(ans, v);
            if (w <= MAXV)
                dp[w] = max(dp[w], v);
        }
    }

    printf("%lld\n", ans);
}
