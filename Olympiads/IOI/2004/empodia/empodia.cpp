#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct State {
    int val;
    int pos;
    int max_val;
    int latest_able;
};

int n;
vector<State> s;
vector<int> a;
set<int> inserted;
vector<pi> ans;

bool empodio(State st, int a, int apos)
{
    if (st.max_val > a)
        return false;

    return apos - st.pos == a - st.val;
}

int main(void)
{
    scanf("%d", &n);
    a.resize(n);
    inserted.insert(n - 1);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // s.push_back({0, 0, 0, n - 1});
    for (int i = 0; i < n; i++) {
        while (!s.empty() && s.back().val > a[i]) {
            int pmax = s.back().max_val;
            s.pop_back();
            if (!s.empty())
                s.back().max_val = max(s.back().max_val, pmax);
        }
        while (!s.empty() && !empodio(s.back(), a[i], i) && s.back().latest_able <= max(a[i], s.back().max_val)) {
            int pmax = s.back().max_val;
            s.pop_back();
            if (!s.empty())
                s.back().max_val = max(s.back().max_val, pmax);
        }
        if (!s.empty() && empodio(s.back(), a[i], i)) {
            ans.push_back(mp(s.back().pos, i));
            s.clear();
        }

        int minrm = *inserted.upper_bound(a[i]);
        s.push_back({a[i], i, a[i], minrm});
        inserted.insert(a[i]);
    }

    printf("%d\n", (int)ans.size());
    for (auto p : ans) {
        printf("%d %d\n", p.first + 1, p.second + 1);
    }

    return 0;
}