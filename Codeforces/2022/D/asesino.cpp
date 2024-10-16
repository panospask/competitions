#include <bits/stdc++.h>

using namespace std;

int N;

// 0 if same, 1 if different
int ask(int i, int j)
{
    printf("? %d %d\n", i + 1, j + 1);
    fflush(stdout);

    int r;
    scanf("%d", &r);

    return !r;
}

bool consistent(int i, int j)
{
    return ask(i, j) == ask(j, i);
}

bool consistent(int i)
{
    int j = 0;
    if (j == i) {
        j = N - 1;
    }

    return consistent(i, j);
}

int find_in_pair(int a1, int a2)
{
    if (consistent(a1)) {
        return a2;
    }
    else {
        return a1;
    }

    return -1;
}

void solve(void)
{
    scanf("%d", &N);

    int ans = -1;
    
    int p = 0;
    if (N % 2) {
        int v0 = ask(0, 1);
        int v1 = ask(1, 2);
        int v2 = (N == 3 ? v0 ^ v1 ^ 1 : ask(2, 0));
        if (v0 ^ v1 ^ v2 == 1) {
            // It's in here
            if (ask(1, 0) != v0) {
                if (ask(2, 1) != v1) {
                    ans = 1;
                }
                else {
                    ans = 0;
                }
            }
            else {
                ans = 2;
            }
        }
        p = 3;
    }

    for (int i = p + 1; i < N - 2 && ans == -1; i += 2) {
        if (!consistent(i - 1, i)) {
            ans = find_in_pair(i - 1, i);
        }
    }
    if (ans == -1) {
        ans = find_in_pair(N - 2, N - 1);
    }

    printf("! %d\n", ans + 1);
    fflush(stdout);
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