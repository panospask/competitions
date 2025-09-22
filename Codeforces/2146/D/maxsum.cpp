#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (!(!((var) & (1LL << (pos)))))

using namespace std;

typedef long long ll;

int l, r;

// The first (times) numbers in v contain bit
ll calculate(vector<int>& v, int upper) {
    if (v.empty()) {
        return 0;
    }
    if (v.size() == 1) {
        return v.front() % (1LL << (upper));
    }
    // Find bit in which numbers break
    int split = 0;

    for (int b = upper - 1; b >= 0; b--) {
        if (!(CHECK_BIT(v.front(), b)) && (CHECK_BIT(v.back(), b))) {
            // Found it
            split = b;
            break;
        }
    }

    ll res = 0;
    int first = 0;
    while (CHECK_BIT(v[first], split) == false) {
        first++;
    }
 
    // Everything above split is homogenous
    for (int b = upper - 1; b > split; b--) {
        if (CHECK_BIT(r, b)) {
            res += (ll)(1LL << b) * v.size();
        }
    }

    // Merge first and last
    int last = first - 1;
    while (last >= 0 && first < v.size()) {
        swap(v[last], v[first]);
        last--;
        first++;

        res += 2 * (ll)((1LL << (split + 1)) - 1);
    }

    // Merge the remaining
    if (first < v.size()) {
        vector<int> nxt(v.begin() + first, v.end());
        res += calculate(nxt, split) + (ll)(1LL << split) * nxt.size();
        for (int i = first; i < v.size(); i++) {
            v[i] = nxt[i - first];
        }
    }
    else if (last >= 0) {
        vector<int> nxt(v.begin(), v.begin() + last + 1);
        res += calculate(nxt, split);
        for (int i = 0; i <= last; i++) {
            v[i] = nxt[i];
        }
    }

    return res;
}

void solve(void) {
    scanf("%d %d", &l, &r);

    vector<int> ans(r - l + 1);
    for (int i = l; i <= r; i++) {
        ans[i - l] = i;
    }

    ll res = calculate(ans, 31);

    printf("%lld\n", res);
    for (int i = 0; i <= r - l; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}