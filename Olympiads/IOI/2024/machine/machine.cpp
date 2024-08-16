#include "machine.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXBITS = 8;

int N;
vector<int> A;
vector<int> B;
vector<int> cnt;
vector<int> pos;

bool test(vector<int>& B, int X)
{
    for (int i = 0; i < N; i++) {
        int cur = B[i] ^ X;

        if (cur >= 2*N + 2 || pos[cur] == -1) {
            return false;
        }
    }

    return true;
}

void update_cnt(int i)
{
    int b = 0;
    while (b < MAXBITS) {
        if (i % 2) {
            cnt[b]++;
        }
        else {
            cnt[b]--;
        }

        i /= 2;
        b++;
    }
}

bool perfect(int i)
{
    while (i >= 2) {
        if (i % 2) {
            return false;
        }
        i /= 2;
    }

    return true;
}

void replace(int i, int j)
{
    pos[A[i]] = -1;
    A[i] = j;
    pos[j] = i;
}

vector<int> find_permutation(int n) {
    N = n;

    A.resize(N, 0);
    cnt.assign(MAXBITS, 0);
    pos.assign(2 * N + 2, -1);

    for (int i = 0; i < N; i++) {
        A[i] = i;
        pos[A[i]] = i;

        update_cnt(i);
    }

    if (N % 2 == 0) {
        replace(0, N);
        if (perfect(N + 2)) {
            replace(1, N + 1);
            replace(2, N + 2);
        }
    }

    vector<int> B = use_machine(A);

    int X = 0;
    while (!test(B, X)) {
        X++;
    }

    for (int i = 0; i < N; i++) {
        B[i] = B[i] ^ X;
        B[i] = pos[B[i]];
    }

    return B;
}
