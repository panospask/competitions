#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> biggest_gap;
vector<int> second_biggest;
vector<int> prv;

void solve(void)
{
    biggest_gap.clear();
    second_biggest.clear();
    prv.clear();

    scanf("%d %d", &n, &k);

    biggest_gap.resize(k, 0);
    second_biggest.resize(k, 0);
    prv.assign(k, -1);

    for (int i = 0; i < n; i++) {
        int col;
        scanf("%d", &col);
        col--;

        int gap = i - prv[col];
        if (biggest_gap[col] < gap) {
            second_biggest[col] = biggest_gap[col];
            biggest_gap[col] = gap;
        }
        else if (second_biggest[col] < gap) {
            second_biggest[col] = gap;
        }

        prv[col] = i;
    }
    for (int c = 0; c < k; c++) {
        int gap = n - prv[c];
        if (biggest_gap[c] < gap) {
            second_biggest[c] = biggest_gap[c];
            biggest_gap[c] = gap;
        }
        else if (second_biggest[c] < gap) {
            second_biggest[c] = gap;
        }
    }

    int ans = INT_MAX;
    for (int c = 0; c < k; c++) {
        int v = biggest_gap[c] / 2 + biggest_gap[c] % 2;
        v = max(v, second_biggest[c]);
        ans = min(ans, v);
    }

    printf("%d\n", max(ans - 1, 0));
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}