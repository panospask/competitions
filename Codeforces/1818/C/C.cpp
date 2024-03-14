#include <bits/stdc++.h>

using namespace std;

int n, q;
vector<int> a;
vector<int> rmove;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int cons_geq = 0;
    for (int i = 1; i < n; i++) {
        if (a[i-1] >= a[i]) {
            cons_geq++;
            if (cons_geq >= 2) {
                rmove.push_back(i - 2);
            }
        }
        else
            cons_geq = 0;
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;
        if (r - l + 1 <= 2) {
            printf("%d\n", r - l + 1);
            continue;
        }

        int rmove_begin = lower_bound(rmove.begin(), rmove.end(), l) - rmove.begin();
        int rmove_end = upper_bound(rmove.begin(), rmove.end(), r - 2) - rmove.begin();
        int total = rmove_end - rmove_begin;

        int ans =  r - l + 1 - total;
        printf("%d\n", ans);
    }

    return 0;
}