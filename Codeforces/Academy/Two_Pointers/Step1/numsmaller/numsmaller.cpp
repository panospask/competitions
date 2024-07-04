#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> a;
vector<int> b;
vector<int> sm;

int main(void)
{
    scanf("%d %d", &N, &M);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    b.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &b[i]);
    }

    int i = 0, j = 0;
    while (i < N || j < M) {
        if (j == M || (i != N && a[i] < b[j])) {
            i++;
        }
        else {
            printf("%d ", i);
            j++;
        }
    }
    printf("\n");

    return 0;
}