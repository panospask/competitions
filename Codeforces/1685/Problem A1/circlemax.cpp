#include <bits/stdc++.h>

using namespace std;

void print_path(int* a, int n)
{
    int b[n];
    for (int i = 0; i < n; i += 2)
        b[i] = a[i/2];
    for (int i = 1; i < n; i += 2)
        b[i] = a[n/2 + i / 2];

    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);

    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);

        int a[n];
        for (int i = 0; i < n; i++) {
                scanf("%d", &a[i]);
            }

        if (n % 2 == 1) {
            printf("NO\n");
        }
        else {

            sort(a, a+n);

            bool path_exist = true;
            for (int i = n - 2; i >= n / 2 && path_exist; i--)
                if (a[i] <= a[i - n/2 + 1])
                    path_exist = false;

            if (!path_exist)
                printf("NO\n");
            else {
                print_path(a, n);
            }
        }
    }
}