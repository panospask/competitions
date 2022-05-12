#include <bits/stdc++.h>

using namespace std;

int dp[1000000][5][5][5];
bool proccess[1000000][5][5][5] = {false};
int n, m;

int find_cases(int k, int low, int high, int cur_diff)
{
    if (high - low > 2)
        return 0;
    if (k == n)
        return 1;

    if (proccess[k][low][high][cur_diff])
        return dp[k][low][high][cur_diff];

    int total = 0;
    total = (total + find_cases(k + 1, min(low, cur_diff-1), high, cur_diff-1)) % m;
    total = (total + find_cases(k + 1, low, max(high, cur_diff+1), cur_diff+1)) % m;

    proccess[k][low][high][cur_diff] = true;
    dp[k][low][high][cur_diff] = total;

    return total;
}

int main(void)
{
    freopen("lingarden.in", "r", stdin);
    freopen("lingarden.out", "w", stdout);
    int high = 0, low = 0, cur_diff = 0;

    cin >> n >> m;

    int result = 1;
    string s;
    cin >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            cur_diff--;
            low = min(cur_diff, low);
        }
        else {
            result = (result + find_cases(i + 1, min(cur_diff - 1, low), high, cur_diff-1)) % m;
            cur_diff++;
            high = max(cur_diff, high);
        }
    }

    cout << result << '\n';
}