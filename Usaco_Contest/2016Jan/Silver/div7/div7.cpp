#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MULTOF 7
#define MAXN 50000

using namespace std;

int arr[MAXN + 10];
int pref_sum[MAXN + 10];
int n;

int main(void)
{
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    scanf("%d", &n);
    pref_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        pref_sum[i] = (pref_sum[i - 1] + arr[i]) % MULTOF;
    }

    int earl_instance, late_instance;
    int maxseq = 0;
    for (int j = 0; j < MULTOF; j++) {
        earl_instance = -1;
        late_instance = -1;
        for (int i = 1; i <= n; i++) {
            if (pref_sum[i] == j && earl_instance == -1) {
                earl_instance = i;
            }
            if (pref_sum[i] == j)
                late_instance = i;
        }

        if (earl_instance != -1)
            maxseq = max(maxseq, late_instance - earl_instance);
    }

    printf("%d\n", maxseq);
    return 0;
}