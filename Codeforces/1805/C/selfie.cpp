#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

vector<int> lines;
int n, m;

void solve(void)
{
    scanf("%d %d", &n, &m);
    lines.clear();

    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        lines.push_back(x);
    }

    sort(lines.begin(), lines.end());

    int a, b, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);

        // if (c <= 0) {
            // Is always good
            // printf("YES\n%d\n", lines[0]);
            // continue;
        // }

        int minval = 0;
        int pos;
        if (lines[n-1] < b) {
            minval = b - lines[n-1];
            pos = n-1;
        }
        else {
            pos = lower_bound(lines.begin(), lines.end(), b) - lines.begin();
            minval = abs(lines[pos] - b);

            if (pos != 0 && minval > abs(lines[pos-1] - b)) {
                minval = abs(lines[pos-1] - b);
                pos--;
            }
        }

        bool ans = (long long int)minval * minval < (long long int)4 * a * c;

        if (ans) {
            printf("YES\n%d\n", lines[pos]);
        }
        else {
            printf("NO\n");
        }
    }

    printf("\n");
}

int t;
int main(void)
{
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();
    
    return 0;
}