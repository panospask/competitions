/* Proves the goldbach hypothesis for N <= 1000000*/

#include <stdio.h>
#include <stdbool.h>

bool isprime(long int number);

int main(void)
{
    freopen("goldbach.in", "r", stdin);
    freopen("goldbach.out", "w", stdout);
    
    long int n;
    scanf("%ld", &n);

    for (long int i = 3; i < n / 2; i += 2) {
        if (isprime(i))
            if (isprime(n - i)) {
                printf("%ld %ld", i, n - i);
                return 0;
            }
    }

    printf("Error!");
    return 0;
}

bool isprime(long int number)
{
    if (number % 2 == 0)
        return false;

    for (long int i = 3; i < number / 2; i += 2)
        if (number % i == 0)
            return false;
        
    return true;
}