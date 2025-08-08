#include <bits/stdc++.h>

using namespace std;

int N, x;
string s;
vector<bool> wall;
set<int> good;

int move_right(int pos) {
    if (pos == N) {
        return 0;
    }

    auto it = good.upper_bound(pos);
    int p = -1;
    if (it != good.end()) {
        p = *it;
        good.erase(p);
        wall[p] = true;
    }

    pos++;
    while (pos != N && !wall[pos]) {
        pos++;
    }

    int ans = 1 + move_right(pos);

    // Undo changes
    if (p != -1) {
        wall[p] = false;
        good.insert(p);
    }

    return ans;
}

int move_left(int pos) {
    if (pos == -1) {
        return 0;
    }

    auto it = good.lower_bound(pos);
    int p = -1;
    if (it != good.begin()) {
        it--;
        p = *it;
        good.erase(p);
        wall[p] = true;
    }

    pos--;
    while (pos >= 0 && !wall[pos]) {
        pos--;
    }

    int ans = 1 + move_left(pos);

    // Undo changes
    if (p != -1) {
        wall[p] = false;
        good.insert(p);
    }

    return ans;
}

void solve(void) {
    cin >> N >> x;
    x--;

    cin >> s;

    wall.resize(N);
    good.clear();
    for (int i = 0; i < N; i++) {
        wall[i] = s[i] == '#';
        if (s[i] == '.') {
            good.insert(i);
        }
    }

    int nxt = x + 1;
    while (nxt < N && !wall[nxt]) {
        nxt++;
    }
    int prv = x - 1;
    while (prv >= 0 && !wall[prv]) {
        prv--;
    }

    int ans = min(move_right(x), move_left(prv) + 1);
    ans = max(ans, min(move_left(x), move_right(nxt) + 1));
    cout << ans << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}