#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void* a, const void* b)
{
    return *(int*) a - *(int*) b;
}

int main(void)
{
    freopen("twingift.in15", "r", stdin);
    freopen("twingift.out", "w", stdout);

    int n, m, low, high;

    scanf("%d %d %d %d", &n, &m, &low, &high);

    int* a_list = malloc(sizeof(*a_list) * n);
    int* b_list = malloc(sizeof(*b_list) * m);
    // int a_list[n];
    // int b_list[m];

    for (int i = 0; i < n; i++) 
        scanf("%d", &a_list[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &b_list[i]);

    if (n > m) {
        ; //SWAP
    }

    qsort(a_list, n, sizeof(int), compare_ints);
    qsort(b_list, m, sizeof(int), compare_ints);

    // int max_m = m - 1;
    int possible_combos = 0;

    // for (int i = 0; i < n; i++) {
    //     int cur_a = a_list[i];
    //     for (int j = max_m; j >= 0; j--) {
    //         int cur_b = b_list[j];
    //         if (cur_a + cur_b > high)
    //             max_m--;
    //         else if (cur_a + cur_b >= low)
    //             possible_combos++;
    //         else {
    //             break;
    //         }
    //     }
    //     if (cur_a > high || max_m == 0)
    //         break;
    // }

    int n_size = n;
    int m_size = m;
    int m_small = 0;
    int m_big = m - 1;

    for (m_small = 0; m_small < m && (a_list[0] + b_list[m_small] < low); m_small++) 
        ;

    for (int i = 0; i < n; i++) {
        int cur_a = a_list[i];
        while (cur_a + b_list[m_small - 1] >= low && m_small > 0)
            m_small--;
        while (cur_a + b_list[m_big] > high && m_big >= 0)
            m_big--;
        
        if (m_big < 0)
            break;
        possible_combos += m_big - m_small + 1;
    }

    printf("%d\n", possible_combos);

}