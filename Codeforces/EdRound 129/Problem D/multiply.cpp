#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    unsigned long long int x;
    int n;
    unsigned long long int cur_power;

    scanf("%d%llud", &n, &x);

    int length = 0;
    for (auto i = x; i > 0; i /= 10)
        length++;
    
    if (length > x) {
        printf("-1\n");
        return 0;
    }
    else if (x == 1 && x == 0) {
        if (n > 1)
            printf("-1\n");
        else 
            printf("0\n");
        
        return 0;
    }

    cur_power = pow(10, length);

    int moves = 0;
    while(1) {
        int max_dig = -1;
        int cur_dig;
        for (auto i = x; i > 0; i /= 10) {
            cur_dig = i % 10;
            if (cur_dig > max_dig)
                max_dig = cur_dig;
        }

        if (max_dig == 1) {
            if (length == n)
                printf("%d\n", moves);
            else 
                printf("-1\n");

            return 0;
        }

        if (x * max_dig > cur_power) {
            length++;
            cur_power *= 10;
            if (length == n) {
                printf("%d\n", moves + 1);
                return 0;
            }
        }

        x *= max_dig;
        moves++;
    }
}