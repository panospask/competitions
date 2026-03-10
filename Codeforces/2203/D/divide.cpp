#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> a, b;

vector<int> cnt;
vector<int> tot;

void solve(void) {
    scanf("%d %d", &N, &M);

    a.resize(N);
    b.resize(M);

    tot.assign(N + M + 1, 0);
    cnt.assign(N + M + 1, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }
    for (int c = 1; c <= N + M; c++) {
        for (int i = 1; c * i <= N + M; i++) {
            tot[c * i] += cnt[c];
        }
    }

    int bob = 0;
    int alice = 0;
    int both = 0;
    for (int i = 0; i < M; i++) {
        scanf("%d", &b[i]);

        if (tot[b[i]] == 0) {
            bob++;
        }
        else if (tot[b[i]] == N) {
            alice++;
        }
        else {
            both++;
        }
    }

    bool awins = false;
    bool swapped = false;
    
    if (both % 2) {
        swapped = true;
        swap(alice, bob);
    }

    awins = (alice > bob);

    if (awins ^ swapped) {
        printf("Alice\n");
    }
    else {
        printf("Bob\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}