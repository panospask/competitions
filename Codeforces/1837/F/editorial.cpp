#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n, k;
vector<int> a;

bool gcomp(const int& a, const int& b)
{
    return a > b;
}

bool is_enough(ll x)
{
    vector<bool> passed;
    vector<bool> using_s;
    priority_queue<int> f;
    vector<pi> rem_s;

    rem_s.resize(n);
    passed.assign(n, false);
    using_s.assign(n, false);

    ll time_taken_s = 0, time_taken_f = 0;
    int elements_s = 0, elements_f = 0;

    int curp = 0;
    for (int i = 0; i < n; i++) {
        rem_s[i] = mp(a[i], i);
    }
    sort(rem_s.begin(), rem_s.end());

    while (curp < n && time_taken_s + rem_s[curp].first <= x) {
        int val, place;
        tie(val, place) = rem_s[curp];
        curp++;
        using_s[place] = true;
        time_taken_s += val;
        elements_s++;
    }
    if (elements_s + elements_f >= k)
        return true;

    for (int i = 0; i < n; i++) {
        if (using_s[i]) {
            elements_s--;
            time_taken_s -= a[i];
            using_s[i] = false;
            while (curp < n && time_taken_s + rem_s[curp].first <= x) {
                int val, place;
                tie(val, place) = rem_s[curp];
                curp++;

                if (passed[place])
                    continue;

                time_taken_s += val;
                using_s[place] = true;
                elements_s++;
            }
        }

        if (time_taken_f + a[i] <= x) {
            f.push(a[i]);
            time_taken_f += a[i];
            elements_f++;
        }
        else if (!f.empty() && a[i] < f.top()) {
            time_taken_f += a[i] - f.top();
            f.pop();
            f.push(a[i]);
        }

        passed[i] = true;
        if (elements_f + elements_s >= k)
            return true;
    }

    return false;
}

void solve(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    ll l = 0;
    ll r = 1;
    while (!is_enough(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (is_enough(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%lld\n", r);
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