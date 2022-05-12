/* Calculates how much time a download will take */

#include <stdio.h>

int main(void)
{
    freopen("downloads.in", "r", stdin);
    freopen("downloads.out", "w", stdout);

    int files;
    scanf("%d", &files);

    int bandwith = 0, downspeed, total_size = 0, time_left;
    for (int i = 0; i < files; i++) {
        scanf("%d %d", &downspeed, &time_left);
        bandwith += downspeed;
        total_size += downspeed * time_left;
    }

    float totaltime_f = (float)total_size / (float)bandwith;
    int totaltime_i = (int)totaltime_f;
    if ((float)totaltime_i + 0.5 <= totaltime_f)
        totaltime_i++;

    printf("%d", totaltime_i);
}