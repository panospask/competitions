#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

int choose(int n, int k) {
    if ((n | k) == n) {
        return 1;
    }
    return 0;
}

int main(void) {
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    int ans = 0;
    int c = 0;
    for (int i = 0; i < N; i++) {
        if (choose(N - 1, i)) {
            ans = ans ^ a[i];
        }
        if (i == N / 2) {
            c++;
        }
    }

    printf("%d\n", ans);

    return 0;
}