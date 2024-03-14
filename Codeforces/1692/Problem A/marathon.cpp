#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int arr[4];
        for (int i = 0; i < 4; i++)
            scanf("%d", &arr[i]);

        int cnt = 0;
        for (int i = 1; i < 4; i++)
            if (arr[i] > arr[0])
                cnt++;

        printf("%d\n", cnt);
    }
}