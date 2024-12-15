#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct Block {
    int start;
    int len;

    int extra;

    int total(void) {
        return start + len + extra;
    }
};

int N;
vector<Block> blocks;
set<pi> available;
ll ans = 0;

int cur = 0, extra = 0, pos = 0;

void add_block(int start, int len, int id)
{
    ans += id * ((ll)start * len + (len) * (len - 1) / 2);
}

void move_next(void)
{
    cur++;
    extra = 0;
}

int main(void)
{
    freopen("diskfrag.in", "r", stdin);
    freopen("diskfrag.out", "w", stdout);

    pos = 0;

    int isgap = 0;
    int c = 0;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        int len;
        scanf("%1d", &len);

        if (isgap) {
            ;
        }
        else {
            blocks.pb({pos, len, 0});
        }

        isgap ^= 1;
        pos += len;
    }

    N = blocks.size();

    pos = 0;
    // The index of the minimum block yet unplaced after pos
    int least = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (blocks[j + 1].start - blocks[j].total() >= blocks[i].len) {
                blocks[i].start = blocks[j].total();
                blocks[j].extra += blocks[i].len;
                break;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        add_block(blocks[i].start, blocks[i].len, i);
    }

    printf("%lld\n", ans);

    return 0;
}