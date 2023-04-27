#include <bits/stdc++.h>
#include "secret.h"

using namespace std;

vector<vector<int>> saved;

// The i-th bit of mask[a] is 1 if a is to the right of the respective mid in that level
int n;
vector<int> mask;
vector<int> vals;

void divide(int lx, int rx, int level)
{
    if (lx == rx - 1)
        return;

    int mid = (lx + rx) / 2;

    saved[level][mid - 1] = vals[mid - 1];
    for (int i = mid - 2; i >= lx; i--)
        saved[level][i] = Secret(vals[i], saved[level][i + 1]);

    saved[level][mid] = vals[mid];
    for (int i = mid + 1; i < rx; i++)
        saved[level][i] = Secret(saved[level][i - 1], vals[i]);
    for (int i = mid; i < rx; i++) {
        // Set the i-th bit to 1 to indicate we are at the right
        mask[i] = mask[i] | (1<<level);
    }

    divide(lx, mid, level + 1);
    divide(mid, rx, level + 1);
}

void Init(int N, int A[])
{
    vals.resize(N);
    for (int i = 0; i < N; i++)
        vals[i] = A[i];

    n = N;
    int levels = ceil(log2(n));

    saved.resize(levels, vector<int>(n));
    mask.resize(n);

    divide(0, n, 0);
}

int Query(int L, int R)
{
    if (L == R)
        return vals[L];

    // Find the first position in which the masks differ => the level we should look at
    int level = __builtin_ctz(mask[L] ^ mask[R]);

    int res = Secret(saved[level][L], saved[level][R]);
    return res;
}