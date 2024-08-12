#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<int> a, b;

void solve(void)
{
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    if (a == b) {
        printf("Bob\n");
        return;
    }

    reverse(b.begin(), b.end());
    if (a == b) {
        printf("Bob\n");
        return;
    }

    printf("Alice\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}