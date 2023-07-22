#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1e9 + 5;

int BLOCK_SIZE;
int N, K;
vector<int> h;

struct Block {
    int min;
    int max;
    int size;

    vector<int> haybells;
};
vector<Block> blocks;

void split(int ind)
{
    Block a = {INF, 0, 0};
    Block b = {INF, 0, 0};

    int mid = blocks[ind].size / 2;
    a.size = mid;
    a.haybells.resize(mid);
    for (int i = 0; i < mid; i++) {
        int v = blocks[ind].haybells[i];
        a.haybells[i] = v;
        a.max = max(a.max, v);
        a.min = min(a.min, v);
    }

    b.haybells.resize(blocks[ind].size - mid);
    b.size = blocks[ind].size - mid;
    for (int i = mid; i < blocks[ind].size; i++) {
        int v = blocks[ind].haybells[i];
        b.haybells[i - mid] = v;
        b.max = max(b.max, v);
        b.min = min(b.min, v);
    }

    blocks.erase(blocks.begin() + ind);
    blocks.insert(blocks.begin() + ind, b);
    blocks.insert(blocks.begin() + ind, a);
}

void insert_at(int b, int v)
{
    // Move as much fwd as possible
    int pos = blocks[b].size;
    blocks[b].haybells.push_back(v);
    while (pos > 0) {
        assert(blocks[b].haybells[pos] == v);

        int w = blocks[b].haybells[pos - 1];
        if (abs(v - w) <= K) {
            swap(blocks[b].haybells[pos], blocks[b].haybells[pos - 1]);
            pos--;
        }
        else
            break;
    }

    // Then move back
    while (pos < blocks[b].haybells.size() - 1) {
        int w = blocks[b].haybells[pos + 1];
        if (w <= v) {
            swap(blocks[b].haybells[pos], blocks[b].haybells[pos + 1]);
            pos++;
        }
        else
            break;
    }

    blocks[b].max = max(blocks[b].max, v);
    blocks[b].min = min(blocks[b].min, v);
    blocks[b].size = blocks[b].haybells.size();

    if (blocks[b].size > BLOCK_SIZE)
        split(b);
}

int main(void)
{
    // freopen("minhay.in", "r", stdin);
    // freopen("minhay.out", "w", stdout);

    scanf("%d %d", &N, &K);
    h.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
    }

    BLOCK_SIZE = sqrt(N);

    blocks.pb({h[0], h[0], 1});
    blocks[0].haybells.push_back(h[0]);
    for (int i = 1; i < N; i++) {
        // Find the earliest position in which i could be placed
        int b = blocks.size() - 1;
        while (b >= 0) {
            if (blocks[b].min + K >= h[i] && h[i] + K >= blocks[b].max)
                b--;
            else
                break;
        }

        // Can be inserted at b and above

        if (b != -1) {
            // Check the latest block to see if any insert position is valid
            bool val = false;
            for (int j = blocks[b].haybells.size() - 1; j >= 0; j--) {
                int v = blocks[b].haybells[j];
                if (abs(v - h[i]) > K)
                    break;

                if (v > h[i])
                    val = true;
            }
            if (val) {
                insert_at(b, h[i]);
                continue;
            }
        }
        b++;

        // Find the first block such that max(block) > h[i]
        while (b < blocks.size() && blocks[b].max <= h[i])
            b++;

        if (b == blocks.size()) {
            // Insert at end
            b--;
        }

        insert_at(b, h[i]);
    }

    for (int b = 0; b < blocks.size(); b++) {
        for (auto h : blocks[b].haybells)
            printf("%d\n", h);
    }

    return 0;
}