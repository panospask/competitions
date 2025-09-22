#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (!(!((var) & (1LL << (pos)))))

using namespace std;

typedef long long ll;

int L, R;
vector<int> ans;

void solve(void) {
    scanf("%d %d", &L, &R);

    ans.resize(R - L + 1);

    int bit = 31;
    int l = L, r = R;

    ll res = 0;

    while (r - l + 1 >= 2) {
        int split = 0;
        for (int b = bit - 1; b >= 0; b--) {
            if (CHECK_BIT(r, b) && !(CHECK_BIT(l, b))) {
                split = b;
                break;
            }
        }

        for (int b = bit - 1; b > split; b--) {
            if (CHECK_BIT(r, b)) {
                res += (1LL << b) * (r - l + 1);
            }
        }

        int first = l;
        while (!(CHECK_BIT(first, split))) {
            first++;
        }

        int last = first - 1;
        while (last >= l && first <= r) {
            ans[last - L] = first;
            ans[first - L] = last;

            first++;
            last--;

            res += 2 * ((1LL << (split + 1)) - 1);
        }

        bit = split;
        if (first <= r) {
            l = first;
            res += (1LL << (split)) * (r - first + 1);
        }
        else if (last >= l) {
            r = last;
        }
        else {
            l = r + 1;
        }
    }
    if (r == l) {
        res += l % (1LL << bit);
        ans[l - L] = l;
    }

    printf("%lld\n", res);
    for (int i = 0; i < ans.size(); i++) {
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