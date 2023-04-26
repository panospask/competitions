#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n, x;
map<int, pi> val_sum;
vector<int> a;

int main(void)
{
    scanf("%d %d", &n, &x);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] + a[j] <= x) {
                int find = x - a[i] - a[j];
                if (val_sum.find(find) != val_sum.end()) {
                    printf("%d %d %d %d\n", val_sum[find].first + 1, val_sum[find].second + 1, i + 1, j + 1);
                    return 0;
                }
            }
        }
        for (int j = 0; j < i; j++) {
            if (a[i] + a[j] <= x)
                val_sum[a[i] + a[j]] = mp(j, i);
        }
    }

    printf("IMPOSSIBLE\n", ans);
    return 0;
}