#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        int a, b, c;

        scanf("%d %d %d", &a, &b, &c);

        if (a + b == c)
            printf("+\n");
        else 

            printf("-\n");
    }

    return 0;
}