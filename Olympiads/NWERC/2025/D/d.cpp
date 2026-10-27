#include <bits/stdc++.h>

using namespace std;

int N;

int main(void) {
    scanf("%d", &N);

    if (N % 2 == 1) {
        printf("%d\n", N / 2);
    }
    else if (N % 4 == 0) {
        printf("%d\n", N / 2 - 1);
    }
    else {
        printf("%d\n", N / 2 - 2);
    }

    return 0;
}