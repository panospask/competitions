#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);

        int min = INT_MAX, secmin = INT_MAX;
        int nums = 0;
        for (int i = n; i != 0; i /= 10) {
            if (i % 10 < min) {
                secmin = min;
                min = i % 10;
            }
            nums++;
        }

        if (nums == 2 && secmin != INT_MAX)
            printf("%d\n", secmin);
        else 
            printf("%d\n",  min);
    }

    return 0;
}