#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<pi> A;

bool comp(pi a, pi b) {
    if (((a.first - 1) / M) == ((b.first - 1) / M)) {
        return a.second < b.second;
    }
    return ((a.first - 1) / M) < ((b.first - 1) / M);
}

int main() {
    scanf("%d %d", &N, &M);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }
    sort(A.begin(), A.end(), comp);

    for (int i = 0; i < N; i++) {
        printf("%d ", A[i].second + 1);
    }
    printf("\n");

    return 0;
}