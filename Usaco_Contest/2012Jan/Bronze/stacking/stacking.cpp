#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000000
#define MAXK 25000

using namespace std;

int final_arr[MAXN + 4];
int mod_stack[MAXN + 4];
int n, k;

int main(void)
{
    freopen("stacking.in", "r", stdin);
    freopen("stacking.out", "w", stdout);

    scanf("%d %d", &n, &k);
    int a, b;
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &a, &b);
        mod_stack[a - 1]++;
        mod_stack[b]--;
    }

    int mod_by = mod_stack[0];
    for (int i = 1; i <= n; i++) {
        final_arr[i - 1] = mod_by;
        mod_by += mod_stack[i];
    }

    sort(final_arr, final_arr + n);
    
    printf("%d\n", final_arr[n / 2]);
    return 0;
}