#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXELE = 50;

int n;
vector<bool> allowed;
vector<int> a;
vector<int> b;
vector<ll> twopow;

bool can_reach(int val, int dest)
{
    vector<bool> reached;
    reached.assign(MAXELE, false);
    reached[val] = true;

    bool found = false;
    for (int cur = val; cur >= dest; cur--) {
        if (!reached[cur])
            continue;

        if (cur == dest) {
            found = true;
            break;
        }

        for (int mod = cur; mod > 0; mod--) {
            if (allowed[mod])
                reached[cur % mod] = true;
        }
    }

    return found;
}

bool test_element_set(void)
{
    for (int i = 0; i < n; i++)
        if (!can_reach(a[i], b[i]))
            return false;

    return true;
}

int main(void)
{
    scanf("%d", &n);
    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    twopow.resize(MAXELE + 1);
    twopow[0] = 1;
    for (int i = 1; i <= MAXELE; i++)
        twopow[i] = twopow[i - 1] * 2;

    allowed.assign(MAXELE + 1, true);
    if (test_element_set() == false) {
        // Initial testing failed
        printf("-1\n");
        return 0;
    }

    ll cost = 0;
    for (int ele = MAXELE; ele > 0; ele--) {
        allowed[ele] = false;
        if (test_element_set() == false) {
            cost += twopow[ele];
            allowed[ele] = true;
        }
    }

    printf("%lld\n", cost);

    return 0;
}