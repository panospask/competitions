#include <bits/stdc++.h>

using namespace std;

const int N = 5000;
const int K = 50;

vector<int> exist;

void remove(int cnt, int l, int r) {
    if (cnt == 1) {
        exist[r - 1] = 0;
        return;
    }

    int mid = (l + r) / 2;
    int c1 = (cnt + 1) / 2;
    remove(c1, l, mid);
    remove(cnt - c1, mid, r);
}

int main(void) {
    exist.assign(N, 1);
    remove(K, 0, N);

    for (int i = 0; i < N; i++) {
        printf("%d ", exist[i]);
    }
    printf("\n");
}