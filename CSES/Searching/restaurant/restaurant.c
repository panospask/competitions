#include <stdio.h>
#include <stdlib.h>

#define MIN_YEAR -100000

int compare_ints(const void* a, const void* b)
{
    return *(int*) a - *(int*) b;
}

int main(void)
{
    int N;
    scanf("%d", &N);

    int l[N];
    int r[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    qsort(l, N, sizeof(int), compare_ints);
    qsort(r, N, sizeof(int), compare_ints);

    int ans = 0;
    int cur = 0;

    int r_p = 0;

    for (int i = 0; i < N; i++) {
        while (r[r_p] < l[i]) {
            cur--;
            r_p++;
        }

        cur++;
        if (cur > ans) {
            ans = cur;
        }
    }

    printf("%d\n", ans);

    return 0;
}