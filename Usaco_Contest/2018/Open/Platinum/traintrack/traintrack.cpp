#include "grader.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

// Returns true if the block starting at i contains j
bool inside(int i, int j, int K)
{
    return i <= j && i + K > j;
}

void helpBessie(int ID)
{
    int N = getTrainLength();
    int K = getWindowLength();
    int BLOCK_SIZE = sqrt(N);

    int pos = getCurrentCarIndex();

    if (getCurrentPassIndex() == 0) {
        // Morning pass
        // Only calculate the answer for places that are multiples of sqrt(N)

        for (int i = 0; i <= N - K; i += BLOCK_SIZE) {
            if (inside(i, pos, K)) {
                int v = get(i / BLOCK_SIZE);
                if (!v)
                    v = INT_MAX;
                if (v > ID)
                    set(i / BLOCK_SIZE, ID);
            }
        }
    }
    else {
        // Afternoon pass
        // Start at position BLOCK_SIZE + 1
        // Maintain the minimum in all places of this block

        int cur_block = (std::max(pos - K + 1, 0) / BLOCK_SIZE);
        int start = cur_block * BLOCK_SIZE;
        for (int i = start; i < N && i < start + BLOCK_SIZE; i++) {
            if (inside(i, pos, K)) {
                ;
            }
        }
    }
}