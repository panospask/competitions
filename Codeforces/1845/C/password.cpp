#include <bits/stdc++.h>

using namespace std;

int m;
string s;
vector<int> l;
vector<int> r;

vector<vector<int>> appears_at;

vector<int> earliest_loss;

vector<int> win_after;

bool try_position(int pos, int min_ind)
{
    return win_after[pos] <= min_ind;
}

bool test_good(int pos, int idx)
{
    for (int d = l[pos]; d <= r[pos]; d++) {
        int n_idx = lower_bound(appears_at[d].begin(), appears_at[d].end(), idx) - appears_at[d].begin();
        if (n_idx == appears_at[d].size())
            return true;
        else
            if (try_position(pos + 1, appears_at[d][n_idx] + 1))
                return true;
    }

    return false;
}

void find_win(int pos)
{
    int l = -1;
    int r = s.size() + 1;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (test_good(pos, mid))
            r = mid;
        else
            l = mid;
    }

    win_after[pos] = r;
}

void solve(void)
{
    l.clear();
    r.clear();
    s.clear();
    win_after.clear();
    appears_at.clear();

    cin >> s;
    cin >> m;

    appears_at.resize(10);
    for (int i = 0; i < s.size(); i++)
        appears_at[s[i] - '0'].push_back(i);

    l.resize(m);
    r.resize(m);
    win_after.assign(m, -1);
    win_after.push_back(s.size() + 1);
    for (int i = 0; i < m; i++)
        scanf("%1d", &l[i]);
    for (int i = 0; i < m; i++)
        scanf("%1d", &r[i]);

    for (int pos = m - 1; pos >= 0; pos--)
        find_win(pos);

    if (win_after[0] == 0)
        printf("YES\n");
    else
        printf("NO\n");
}

int main(void)
{
    int t;
    cin >> t;

    while (t--)
        solve();
}