#include <bits/stdc++.h>

using namespace std;

const int BITS = 32;
const int EXPONENT = 8;
const int FRACTION = 23;

vector<int> C;
vector<vector<int>> L;

// Return the integer value from positions [i..j) to v
int positions(int v, int i, int j)
{
    int len = j - i;
    v >>= i;

    return v & ((1 << len) - 1);
}

int FAM(void)
{
    int i, j, k;
    scanf("%d %d %d", &i, &j, &k);

    int ii = C[i], ij = C[j], ik = C[k], ians;

    float fi, fj, fk, fans;
    memcpy(&fi, &ii, sizeof(int));
    memcpy(&fj, &ij, sizeof(int));
    memcpy(&fk, &ik, sizeof(int));

    fans = fi * fj + fk;

    memcpy(&ians, &fans, sizeof(int));

    return ians;
}

int LUT(void)
{
    int i, j, b;
    scanf("%d %d %d", &i, &j, &b);

    int mask = positions(C[0], j, j + b);

    return L[i][mask];
}

int NAND(void)
{
    int i, j;
    scanf("%d %d", &i, &j);

    return ~(C[i] & C[j]);
}

int CON(void)
{
    int x;
    scanf("%x", &x);

    return x;
}

void solve(void)
{
    int Q, x;
    scanf("%x", &x);

    int N;
    scanf("%d", &N);
    L.assign(N, vector<int>());
    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);
        L[i].resize(k);
        for (int j = 0; j < k; j++) {
            scanf("%x", &L[i][j]);
        }
    }

    scanf("%d", &Q);
    C.resize(Q + 1);
    C[0] = x;

    for (int i = 1; i <= Q; i++) {
        char comm;
        scanf(" %c", &comm);

        if (comm == 'C') {
            C[i] = CON();
        }
        else if (comm == 'L') {
            C[i] = LUT();
        }
        else if (comm == 'N') {
            C[i] = NAND();
        }
        else {
            C[i] = FAM();
        }
    }

    printf("%x\n", C[Q]);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}