#include <bits/stdc++.h>

using namespace std;

string t, p;
vector<int> a;
vector<int> removed_at;

bool can_make_with_n_removed(int n)
{
    int p_pos = 0;
    int t_pos = 0;
    for (t_pos = 0; t_pos < t.size() && p_pos < p.size(); t_pos++) {
        if (removed_at[t_pos] > n && t[t_pos] == p[p_pos])
            p_pos++;
    }

    return p_pos == p.size();
}

int main(void)
{
    cin >> t >> p;
    a.resize(t.size());
    removed_at.resize(t.size());
    for (int i = 0; i < t.size(); i++) {
        scanf("%d", &a[i]);
        removed_at[a[i] - 1] = i + 1;
    }

    int l = 0; // can_make_with_n_removed(l) = true
    int r = t.size(); // can_make_with_n_removed(r) = false
    while (r > l + 1) {
        int mid = (r + l) / 2;
        if (can_make_with_n_removed(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%d\n", l);
    return 0;
}