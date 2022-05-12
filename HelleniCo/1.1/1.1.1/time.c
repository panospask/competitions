/* Calculates the time based on the broken clock */

#include <stdio.h>

int main(void)
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    
    int hours, minutes, seconds;
    scanf("%d:%d:%d", &hours, &minutes, &seconds);

    int totalseconds = 3600 * hours + 60 * minutes + seconds;
    totalseconds *= 2;
    
    hours = totalseconds / 3600;
    minutes = (totalseconds % 3600) / 60;
    seconds = (totalseconds % 3600) % 60;

    printf("%.2d:%.2d:%.2d", hours, minutes, seconds);
}