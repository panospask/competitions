#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a;

void solve(void)
{
    scanf("%d", &N);
    a.resize(N);

    ll prod = 1;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        if (a[i] < 0)
            prod *= -1;
        else if (a[i] == 0)
            prod *= 0;
    }

    if (prod > 0) {
        printf("1\n1 0\n");
    }
    else {
        printf("0\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}