#include <bits/stdc++.h>
#define MAXN 1000000

using namespace std;

int divisornum[MAXN + 2];
long long int ans[MAXN + 2];
int n = 1000000, x;

int main(void)
{
    scanf("%d", &x);

    for (int i = 2; i <= n; i++) {
        if (divisornum[i] == 0) {
            for (int j = i * 2; j <= n; j += i) {
                divisornum[j] = 1;
                int modby = 0;
                int number = j;
                while (!(number % i)) {
                    modby++;
                    number /= i;
                }

                if (ans[j] == 0)
                    ans[j] = modby + 1;
                else 
                    ans[j] *= modby + 1;
            }
        }
    }

    int num;
    for (int q = 0; q < x; q++) {
        scanf("%d", &num);

        if (num != 1)
            printf("%lld\n", max(ans[num], 2ll));
        else 
            printf("1\n");
    }

    return 0;
}