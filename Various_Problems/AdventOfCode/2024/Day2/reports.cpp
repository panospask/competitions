#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e9;

bool safe(vector<int> v)
{
    bool good = true;
    int s = 0;
    for (int i = 1; i < v.size(); i++) {
        int prv = v[i - 1];
        int cur = v[i];

        int d = cur - prv;
        if (d == 0) {
            good = false;
            continue;
        }

        if (s == 0) {
            s = d / abs(d);
        }
        good = good && (d * s > 0) && abs(d) <= 3;
    }

    return good;
}

int main(void)
{
    freopen("reports.in", "r", stdin);
    freopen("reports.out", "w", stdout);

    int c = '\0';
    int ans = 0;
    while (c != EOF) {
        // New report

        vector<int> v;
        for (c = 0; c != EOF && c != '\n'; c = getchar()) {
            int a;
            scanf("%d", &a);
            v.pb(a);
        }

        for (int i = 0; i < v.size(); i++) {
            vector<int> t;
            for (int j = 0; j < v.size(); j++) {
                if (j != i) {
                    t.pb(v[j]);
                }
            }

            if (safe(t)) {
                ans++;
                break;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}