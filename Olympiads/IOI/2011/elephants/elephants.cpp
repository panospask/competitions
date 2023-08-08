#include "elephants.h"
#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Block {
  vector<int> positions;

  // photos[i]: Photos required and maximum position if the first elephant to be photographed is i
  vector<pi> photos;

    int size(void) {
        return positions.size();
    }
};

int N, L;
int upd = 0;
int ttl_blocks;
int BLOCK_SIZE;
vector<int> loc;
vector<Block> blocks;

bool onlyfirst(const pi& a, const pi& b)
{
    return a.f < b.f;
}

void create_photos(Block& b)
{
    int sz = b.positions.size();
    b.photos.resize(sz);

    int r = sz;
    for (int i = sz - 1; i >= 0; i--) {
        while (r > i + 1 && b.positions[r - 1] > b.positions[i] + L)
            r--;

        if (r == sz) {
            b.photos[i] = mp(b.positions[i] + L + 1, 1);
        }
        else {
            b.photos[i] = b.photos[r];
            b.photos[i].s++;
        }
    }
}

// Merge blocks b and b + 1
void merge_blocks(int b)
{
    for (int i = 0; i < blocks[b + 1].size(); i++)
        blocks[b].positions.push_back(blocks[b + 1].positions[i]);

    blocks.erase(blocks.begin() + b + 1);

    create_photos(blocks[b]);
}

// Split block b
void split_block(int b)
{
    int mid = blocks[b].size() / 2;

    Block b1, b2;
    for (int i = 0; i < mid; i++)
        b1.positions.push_back(blocks[b].positions[i]);
    for (int i = mid; i < blocks[b].size(); i++)
        b2.positions.push_back(blocks[b].positions[i]);

    blocks.erase(blocks.begin() + b);
    blocks.insert(blocks.begin() + b, b2);
    blocks.insert(blocks.begin() + b, b1);

    create_photos(blocks[b]);
    create_photos(blocks[b + 1]);
}

void init(int n, int l, int X[])
{
    N = n;
    L = l;
    BLOCK_SIZE = 500;

    loc.resize(N);

    blocks.resize(1);
    for (int i = 0; i < N; i++) {

        blocks[i / BLOCK_SIZE].positions.push_back(X[i]);
        loc[i] = X[i];

        if (i + 1 == N || (i + 1) % BLOCK_SIZE == 0) {
            create_photos(blocks[i / BLOCK_SIZE]);
            if (i + 1 != N) {
                blocks.push_back({vector<int>(), vector<pi>()});
            }
        }
    }
}

void insert_at(int i, int v)
{
    int pos = lower_bound(blocks[i].positions.begin(), blocks[i].positions.end(), v) - blocks[i].positions.begin();

    blocks[i].positions.insert(blocks[i].positions.begin() + pos, v);

    // if (blocks[i].size() >= BLOCK_SIZE) {
    //     split_block(i);
    // }
    // else {
        create_photos(blocks[i]);
    // }
}

void remove_from(int i, int v)
{
    int pos = lower_bound(blocks[i].positions.begin(), blocks[i].positions.end(), v) - blocks[i].positions.begin();

    blocks[i].positions.erase(blocks[i].positions.begin() + pos);

    if (blocks[i].size() == 0) {
        blocks.erase(blocks.begin() + i);
    }
    // else if (i != blocks.size() - 1 && blocks[i].size() + blocks[i + 1].size() <= BLOCK_SIZE) {
    //     merge_blocks(i);
    // }
    // else if (i && blocks[i - 1].size() + blocks[i].size() <= BLOCK_SIZE) {
    //     merge_blocks(i - 1);
    // }
    else {
        create_photos(blocks[i]);
    }
}

pi calculate_block(int i, int pos)
{
    Block b = blocks[i];
    if (b.positions.back() < pos)
        return mp(pos, 0);

    int at = lower_bound(b.positions.begin(), b.positions.end(), pos) - b.positions.begin();

    return b.photos[at];
}

int update(int pos, int y)
{
    // After some updates, rebuild
    upd++;
    if (upd == 490) {
        blocks.clear();
        vector<int> p = loc;
        sort(p.begin(), p.end());
        blocks.resize(1);
        for (int i = 0; i < N; i++) {

            blocks[i / BLOCK_SIZE].positions.push_back(p[i]);

            if (i + 1 == N || (i + 1) % BLOCK_SIZE == 0) {
                create_photos(blocks[i / BLOCK_SIZE]);
                if (i + 1 != N) {
                    blocks.push_back({vector<int>(), vector<pi>()});
                }
            }
        }
        upd = 0;
    }

    // Find the block in which i belongs to and in which block it will go
    // First remove the element
    int prev = loc[pos];
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].positions.back() >= prev) {
            // Insert at previous block
            remove_from(i, prev);
            break;
        }
    }

    loc[pos] = y;
    // Then insert
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].positions.back() >= y || i == blocks.size() - 1) {
            // Insert at previous block
            insert_at(i, y);
            break;
        }
    }

    // Recalculate the photos
    pi ans = mp(0, 0);
    for (int b = 0; b < blocks.size(); b++) {
        pi nxt = calculate_block(b, ans.f);

        ans.f = nxt.f;
        ans.s += nxt.s;
    }

    return ans.s;
}
