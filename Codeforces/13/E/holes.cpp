#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

const int INF = INT_MAX;

struct move {
    int target, steps, last;
};
typedef struct move Move;

int n, q;
vector<int> power;
vector<Move> move_next_block;
vector<int> block;
int block_size, total_blocks;

void update_power(int x, int k)
{
    power[x] = k;
    for (int i = min(block_size * (block[x] + 1) - 1, n-1); i >= block_size * block[x]; i--) {
        int nxt = i + power[i];
        if (nxt >= n) {
            move_next_block[i] = {INF, 1, i};
        }
        else if (block[nxt] > block[i]) {
            move_next_block[i] = {nxt, 1, i};
        }
        else {
            move_next_block[i] = move_next_block[nxt];
            move_next_block[i].steps++;
        }
    }
}

ii find_for_hole(int x)
{
    int steps = 0;
    int prev = -1;
    int cur = x;
    while (cur != INF) {
        steps += move_next_block[cur].steps;
        prev = move_next_block[cur].last;
        cur = move_next_block[cur].target;
    }

    return mp(steps, prev);
}

int main(void)
{
    scanf("%d %d", &n, &q);
    power.resize(n);
    block.resize(n);
    move_next_block.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &power[i]);

    // Create the blocks
    block_size = sqrt(n);
    total_blocks = (n-1) / block_size + 1;
    block.resize(n);
    for (int i = 0; i < n; i++)
        block[i] = i / block_size;

    for (int i = n - 1; i >= 0; i--) {
        int nxt = i + power[i];
        if (nxt >= n) {
            move_next_block[i] = {INF, 1, i};
        }
        else if (block[nxt] > block[i]) {
            move_next_block[i] = {nxt, 1, i};
        }
        else {
            move_next_block[i] = move_next_block[nxt];
            move_next_block[i].steps++;
        }
    }

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x, k;
            scanf("%d %d", &x, &k);
            x--;
            update_power(x, k);
        }
        else {
            int x;
            scanf("%d", &x);
            x--;
            ii ans = find_for_hole(x);
            printf("%d %d\n", ans.second + 1, ans.first);
        }
    }

    return 0;
}