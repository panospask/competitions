#include <bits/stdc++.h>
#define MAXN 1000000

using namespace std;

int n, k;
int elements[MAXN + 2];
unordered_map<int, int> chems_with_num_mod_k;

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
        elements[i] %= k;
    }

    int l = 0;
    int r = 0;
    int ans = 0;
    while (r != n) {
        int cur = elements[r];
        int complement = (k - cur) % k;

        while (chems_with_num_mod_k[complement] != 0) {
            chems_with_num_mod_k[elements[l]]--;
            l++;
        }

        chems_with_num_mod_k[elements[r]]++;
        ans = max(ans, r - l + 1);
        r++;
    }

    printf("%d\n", ans);
    return 0;
}