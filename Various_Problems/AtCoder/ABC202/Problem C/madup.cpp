#include <bits/stdc++.h>
#define MAXN (int)(10e5)

using namespace std;

int b[MAXN];
int n;
map<int, int> a;
map<int, int> c;

int main(void)
{
    scanf("%d", &n);    

    // Read a
    int val;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        a[val]++;
    }
    // Read b
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    // Read c
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        c[val]++;
    }

    long long int ans = 0;
    
    int a_val, c_val;
    for (int i = 0; i < n; i++) {
        a_val = a[b[i]];
        c_val = c[i + 1];

        ans += a_val * (long long int)c_val;
    }

    printf("%lld\n", ans);
    return 0;
}