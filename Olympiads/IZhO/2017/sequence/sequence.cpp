#include <bits/stdc++.h>

using namespace std;

int N;

int max_value;
vector<int> dp;
vector<int> cur;
vector<int> prv;

vector<int> a;
vector<int> k;

void print_ans(int pos)
{
    vector<int> ans;
    for (int i = pos; i != -1; i = prv[i])
        ans.push_back(i);
    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (auto i : ans)
        printf("%d ", i + 1);
    printf("\n");

}

int solve_normal(void)
{
    dp.resize(N);
    prv.resize(N);

    int maxv = 0, maxpos = 0;
    for (int i = 0; i < N; i++) {
        dp[i] = 0;
        prv[i] = -1;

        for (int j = i - 1; j >= 0; j--) {
            if (__builtin_popcount(a[i] & a[j]) == k[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prv[i] = j;
            }
        }

        if (dp[i] > maxv) {
            maxv = dp[i];
            maxpos = i;
        }
    }

    print_ans(maxpos);
    return 0;
}

int solve_bitwise(void)
{
    dp.assign(max_value + 1, -1);
    cur.resize(max_value + 1);
    prv.resize(N);


    int opt_v = 0;
    int opt_pos = 0;
    for (int i = 0; i < N; i++) {
        prv[i] = -1;

        int bestprv = -1;
        int bestv = 0;
        for (int j = 0; j <= max_value; j++) {
            if (dp[j] != -1 && __builtin_popcount(j & a[i]) == k[i] && bestv < dp[j] + 1) {
                bestv = dp[j] + 1;
                bestprv = cur[j];
            }
        }

        prv[i] = bestprv;
        if (dp[a[i]] < bestv) {
            dp[a[i]] = bestv;
            cur[a[i]] = i;
        }

        if (bestv > opt_v) {
            opt_v = bestv;
            opt_pos = i;
        }
    }

    print_ans(opt_pos);
    return 0;
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    k.resize(N);
    max_value = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        max_value = max(max_value, a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &k[i]);
    }

    if (max_value <= (1 << 8))
        solve_bitwise();
    else
        solve_normal();

    return 0;
}