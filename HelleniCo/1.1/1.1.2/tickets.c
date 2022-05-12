/* Calculates the cheapest possible solution for N people */

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    freopen("tickets.in", "r", stdin);
    freopen("tickets.out", "w", stdout);

    int n, a, b, c, d;
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);

    int min_ticketcost;
    bool lower = false;
    
    if (a > n) {
        min_ticketcost = n * 10;
        if (a * 9 < min_ticketcost)
            min_ticketcost = a * 9;
        lower = true;
    }

    if (b > n) {
        if (!lower) {
            min_ticketcost = n * 10 - 0.1 * n * 10;
            lower = true;
        }
        if (b * 8 < min_ticketcost)
            min_ticketcost = b * 8;
            
    }

    if (c > n) {
        if (!lower) {
            min_ticketcost = n * 10 - 2 * n;
            lower = true;
        }
        if (((c * 10) - 3 * c) < min_ticketcost)
            min_ticketcost = c * 7;
    }

    if (d > n) {
        if (!lower)
            min_ticketcost = n * 7;
        if (d * 5 < min_ticketcost)
            min_ticketcost = d * 5;
    }

    else 
        min_ticketcost = n * 5;

    printf("%d", min_ticketcost);

    return 0;
}