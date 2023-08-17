#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
string S;

bool sign(int a)
{
    return a >= 0;
}

pi calc_max_under(int l)
{
    int best = 0;
    pi res = make_pair(0, 0);

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int u = i;
            int v = j;
            if (S[i] == '0' && S[j] == '1')
                swap(u, v);

            if (S[u] != '1' || S[v] != '0')
                continue;

            if (sign(v - u) == sign(l) && abs(v - u) <= abs(l) && abs(v - u) > abs(best)) {
                best = v - u;
                res = make_pair(v, u);
            }
        }

    return res;
}

int main(void)
{
    cin >> S;
    N = S.size();

    int cur_sum = 0;
    int target_sum = 0;

    int M = 0;
    for (int i = 0; i < N; i++)
        if (S[i] - '0') {
            M++;
            cur_sum += i + 1;
        }

    target_sum = 2 * N * M - N * N + N * (N + 1) / 2 - M * (M - 1) / 2 + (N - M) * (N - M - 1) / 2;
    target_sum /= 2;

    int ans = 0;
    while (target_sum - cur_sum) {
        pi r = calc_max_under(target_sum - cur_sum);
        swap(S[r.first], S[r.second]);

        ans++;
        cur_sum += r.first - r.second;
    }

    printf("%d\n", ans);
}