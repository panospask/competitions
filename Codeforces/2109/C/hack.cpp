#include <bits/stdc++.h>

using namespace std;

void digit(void) {
    printf("digit\n");
    fflush(stdout);
    int d;
    scanf("%d", &d);
}

int div(int v) {
    printf("div %d\n", v);
    fflush(stdout);
    int d;
    scanf("%d", &d);

    return d;
}

int mul(int v) {
    printf("mul %d\n", v);
    fflush(stdout);
    int d;
    scanf("%d", &d);

    return d;
}

int add(int v) {
    printf("add %d\n", v);
    fflush(stdout);
    int d;
    scanf("%d", &d);

    return d;
}

int answer() {
    printf("!\n");
    fflush(stdout);

    int d;
    scanf("%d", &d);

    return d;
}

void solve(void) {
    int N;
    scanf("%d", &N);

    mul(9);
    digit();
    digit();

    if (N != 9) {
        add(N - 9);
    }

    answer();
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}