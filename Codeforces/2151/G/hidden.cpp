#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;

// Confirmed single in range
vector<int> singles;

// Assumed double in range
vector<int> doubles;

int ask(int v, int l, int r) {
    printf("? %d %d ", v, r - l);

    for (int i = l; i < r; i++) {
        printf("%d ", i);
    }
    printf("\n");

    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

void solve(void) {
    scanf("%d", &N);
    int l = 1; // included
    int r = 2 * N; // excluded

    doubles.clear();
    singles.clear();
    for (int i = 1; i <= N; i++) {
        doubles.push_back(i);
    }

    while (l + 1 < r) {
        int mid = (l + r) / 2;

        // Split to ranges [l, mid) and [mid, r)

        vector<int> status(N + 1, 0);

        int c1 = 0, c2 = 0;
        for (auto v : doubles) {
            int a1 = ask(v, l, mid);
            int a2 = ask(v, mid, r);

            if (a1 && a2) {
                status[v] = 0;
                c1++;
                c2++;
            }
            else if (a1) {
                // Assume full left
                status[v] = 1;
                c1 += 2;
            }
            else {
                // Assume full right
                status[v] = 2;
                c2 += 2;
            }
        }

        for (auto v : singles) {
            int a = ask(v, l, mid);

            if (a) {
                status[v] = 1;
                c1++;
            }
            else {
                status[v] = 2;
                c2++;
            }
        }

        // Whoever exceeds its count contains the false
        int res = (mid - l) != c1 ? 1 : 2;

        if (res == 1) {
            r = mid;
        }
        else {
            l = mid;
        }

        // Now update singles and doubles
        vector<int> nxtdouble;
        vector<int> nxtsingle;
        for (auto v : doubles) {
            if (status[v] == res) {
                nxtdouble.pb(v);
            }
            else if (status[v] == 0) {
                nxtsingle.pb(v);
            }
        }
        for (auto v : singles) {
            if (status[v] == res) {
                nxtsingle.pb(v);
            }
        }

        swap(doubles, nxtdouble);
        swap(singles, nxtsingle);
    }

    printf("! %d\n", doubles.front());
    fflush(stdout);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while(t--) {
        solve();
    }

    return 0;
}