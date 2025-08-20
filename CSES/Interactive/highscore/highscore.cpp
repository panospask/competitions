#include <bits/stdc++.h>

using namespace std;

int N, K;

int ask(int p, int team) {
    if (p > N) {
        return 0;
    }
    if (team) {
        printf("S ");
    }
    else {
        printf("F ");
    }
    printf("%d\n", p);

    fflush(stdout);

    int ans;
    scanf("%d", &ans);

    return ans;
}

int search(int b) {
    int l = 0; // A[l - 1] is definetely higher than K-th element
    int r = K; // A[r] is lower or equal K-th element
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        int v1 = ask(mid, b);
        int v2 = ask(K - mid, !b);

        if (v2 < v1) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return r;
}

int main(void) {
    scanf("%d %d", &N, &K);

    int p1 = search(0);
    int p2 = search(1);

    int v1 = ask(p1, 0);
    int v2 = ask(p2, 1);

    printf("! %d\n", max(v1, v2));
}