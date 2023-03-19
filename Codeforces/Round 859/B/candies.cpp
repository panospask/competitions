#include <bits/stdc++.h>

using namespace std;

int a[1000];

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        int n;

        scanf("%d", &n);
        int m_num = 0;
        int b_num = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[j]);
            if (a[j] % 2)
                b_num += a[j];
            else 
                m_num += a[j]; 
        }

        if (m_num > b_num)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}