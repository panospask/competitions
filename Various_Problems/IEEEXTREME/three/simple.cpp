#include <bits/stdc++.h>

using namespace std;

int N;

int main(void)
{
    scanf("%d", &N);

    vector<int> p23({3});

    while (p23.back() < N) {
        p23.push_back(p23.back() * p23.back());
    }

    int x = 1;
    int ans = 0;
    for (int i = p23.size() - 2; i >= 0; i--) {
        if (x * p23[i] <= N) {
            x = x * p23[i];
            ans += (1 << i);
        }
    }

    if (x == N) {
        printf("%d\n", ans);
    }
    else {
        printf("-1\n");
    }
}