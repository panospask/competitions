#include <bits/stdc++.h>

using namespace std;

int t, n, m;
int main(void)
{
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d %d", &n, &m);

        if (n > m) {
            printf("No\n");
            continue;
        }

        else if (n == m) {
            printf("Yes\n");
            for (int i = 0; i < n; i++) {
                printf("1");
                if (i != n - 1)
                    printf(" ");
                else 
                    printf("\n");
            }

            continue;
        }

        int res = m / n;
        int sub = m % n;

        if ((n - sub) % 2 == 0|| sub == 0) {
            int curnum;
            printf("Yes\n");
            for (int i = 0; i < n; i++) {
                curnum = res;
                if (n - sub <= i)
                    curnum += 1;

                printf("%d", curnum);
                if (i != n-1)
                    printf(" ");
                else 
                    printf("\n");
            }
        }
        else if (n % 2 == 1) {
            printf("Yes\n");
            for (int i = 0; i < n - 1; i++)
                printf("%d ", res);

            printf("%d\n", res+ sub);
        }
        else {
            printf("No\n");
        }
    }
}