#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, T;
int M = 0;
vector<int> A;

bool solve(int K) {
    int rem = 0;
    int cur = K;

    ll t = 0;

    // Gain of skipping some houses until the end
    ll gain = 0;
    int dist = 0;

    ll unused = 0;

    int houses_found = 0;

    for (int i = 0; i < N; i++) {
        // Move one forward
        t++;
        unused++;
        if (rem) {
            dist++;
        }
        if (A[i] == 1) {
            // House
            if (cur && rem == 0) {
                cur--;
            }
            else {
                rem++;
            }
            unused = 0;
        }
        if (A[i] == 2) {
            // Shop
            cur++;
            if (cur == rem) {
                // Go back
                t += (ll)2 * dist;
                unused = dist;
                cur = 0;
                rem = 0;
                dist = 0;
            }
        }
    }

    return t - unused <= T && rem == 0;
}

int main(void) {
    scanf("%d %d", &N, &T);

    A.resize(N);
    M = 0;
    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);
        if (c == 'H') {
            A[i] = 1;
            M++;
        }
        else if (c == 'S') {
            A[i] = 2;
        }
        else {
            A[i] = 0;
        }
    }

    int l = -1;
    int r = M + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (solve(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    if (r == M + 1) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", r);
}