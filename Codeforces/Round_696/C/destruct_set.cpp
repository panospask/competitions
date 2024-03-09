#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N;
multiset<int> nums;
vector<int> a;
vector<pi> op;

bool check(int x)
{
    nums.clear();
    op.clear();
    for (int i = 0; i < 2 * N; i++) {
        nums.insert(a[i]);
    }

    while (nums.size()) {
        int big = *nums.rbegin();
        nums.erase(nums.find(big));

        int small = x - big;
        if (nums.find(small) == nums.end()) {
            return false;
        }

        op.pb(mp(big, small));
        nums.erase(nums.find(small));
        x = big;
    }

    return true;
}

void solve(void)
{
    scanf("%d", &N);

    a.resize(2 * N);
    int m = 0;
    for (int i = 0; i < 2 * N; i++) {
        scanf("%d", &a[i]);
        m = max(m, a[i]);
    }

    bool found = false;
    for (int i = 0; i < 2 * N && !found; i++) {
        found = check(m + a[i]);
    }

    if (found) {
        printf("YES\n%d\n", op[0].first + op[0].second);
        for (int i = 0; i < N; i++) {
            printf("%d %d\n", op[i].first, op[i].second);
        }
    }
    else {
        printf("NO\n");
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}