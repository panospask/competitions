#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long lll;

const int CYCLESIZE = 4;

lll ans = 0;
int k, s;
int cyclesum;
vector<int> cycle;

lll change_at(int v)
{
    lll res = 0;

    int add = 0;
    ll bonuses = 0;

    // For the first v, only increase the bonuses
    bonuses += s + (ll)(v / CYCLESIZE) * cyclesum;

    for (int i = 0; i < v % CYCLESIZE; i++)
        bonuses += cycle[i];

    // For the last k - v, spread bonuses
    res = (lll)bonuses * (k - v);

    return res;
}

void calc_cycle(int b)
{

    int init = b % 10;
    cycle.push_back(init);
    cyclesum += init;

    int cur = (init + init) % 10;
    while (cur != init) {
        cycle.push_back(cur);
        cyclesum += cur;
        cur = (cur + cur) % 10;
    }
}

void solve(void)
{
    cycle.clear();
    cyclesum = 0;
    ans = 0;

    scanf("%d %d", &s, &k);

    if (s == 0) {
        printf("0\n");
        return;
    }

    if (s % 10 == 0) {
        ans = (ll)k * s;
        printf("%lld\n", ans);
        return;
    }
    else if (s % 10 == 5) {
        // Only 1 addition is possible
        ans = (lll)k * s;
        if (k)
        ans = max(ans, (lll)(k - 1) * (s + 5));

        printf("%lld\n", (ll)ans);

        return;
    }

    if (s % 2) {
        ans = (lll)k * s;
        k--;
        s += s % 10;
    }

    calc_cycle(s);

    assert(CYCLESIZE == 4);

    // Time of change
    int l = 0;
    int r = k;

    while (r - l > CYCLESIZE) {
        int m1 = ((ll)l + l + r) / 3;
        int m2 = ((ll)l + r + r) / 3;

        m1 = m1 / CYCLESIZE * CYCLESIZE;
        m1 = max(m1, l);

        m2 = (m2 / CYCLESIZE + 1) * CYCLESIZE;
        m2 = min(m2, r);

        lll r1 = change_at(m1);
        lll r2 = change_at(m2);

        if (r1 > r2) {
            r = m2 - 1;
        }
        else {
            l = m1 + 1;
        }
    }

    for (int i = max(0, l - (int)CYCLESIZE); i <= min(r + (int)CYCLESIZE, k); i++) {
        ans = max(ans, change_at(i));
    }


    string st;
    while (ans) {
        st.push_back(ans % 10 + '0');
        ans /= 10;
    }
    reverse(st.begin(), st.end());

    cout << st << endl;
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