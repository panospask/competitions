#include <bits/stdc++.h>

using namespace std;

int find_third(int n)
{
    int val = 1;
    for (int i = 1; i < n / 3; i++) {
        if (n - i <= 2 * i) {
            break;
        }
        else {
            if ((n - i) % 2 == 1)
                val = i;
        }
    }

    return val;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);

        int thrid = find_third(n);
        int second = (( n - thrid) % 2 == 1 ? ((n - thrid) / 2) : ((n - thrid) / 2) - 1); 
        int first = n - thrid - second;

        printf("%d %d %d\n", second, first, thrid);
    }
    
    return 0;
}