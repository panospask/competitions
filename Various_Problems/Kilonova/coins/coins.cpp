#include <bits/stdc++.h>

using namespace std;

int N;

void solve(void)
{
    scanf("%d", &N);

    if (N <= 3) {
        if (N == 2) {
            printf("Second\n");
        }
        else {
            printf("First\n");
        }
        return;
    }
    if (N % 2 == 0) {
        printf("First\n");
        return;
    }


    bool found = false;
    for (int i = 3; i * i <= N; i++) {
        if (N % i == 0) {
            if (i != 3 || N / i != 3) {
                found = true;
            }
        }
    }

    if (found) {
        printf("First\n");
    }
    else {
        printf("Second\n");
    }
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