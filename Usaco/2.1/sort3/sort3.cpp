/*
ID: panos.p1
LANG: C++
TASK: sort3
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
int arr[1005];
int n;

int main(void)
{
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out", "w", stdout);

    int ones = 0, twos = 0, threes = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] == 1)
            ones++;
        else if (arr[i] == 2)
            twos++;
        else 
            threes++;
    }

    // Which positions should ones, twos and threes occupy sorted
    int one_ending = ones - 1;
    int three_starting = n - threes;

    int f1t3 = 0, f1t2 = 0, f2t1 = 0, f2t3 = 0, f3t1 = 0, f3t2 = 0;

    // Count the values at positions they should not be
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            if (i > one_ending && i < three_starting)
                f1t2++;
            else if (i >= three_starting)
                f1t3++;
        }
        if (arr[i] == 2) {
            if (i <= one_ending)
                f2t1++;
            else if (i >= three_starting)
                f2t3++;
        }
        if (arr[i] == 3) {
            if (i <= one_ending)
                f3t1++;
            else if (!(i >= three_starting))
                f3t2++;
        }
    }

    int s12 = min(f1t2, f2t1);
    int s23 = min(f2t3, f3t2);
    int s13 = min(f1t3, f3t1);

    int swaps = 0;
    swaps += s12 + s13 + s23;

    f1t2 -= s12;
    f2t1 -= s12;
    f2t3 -= s23;
    f3t2 -= s23;
    f1t3 -= s13;
    f3t1 -= s13;

    int total_misplaces = f1t2 + f2t1 + f2t3 + f3t2 + f1t3 + f3t1;

    swaps += (total_misplaces / 3) * 2;

    printf("%d\n", swaps);
    return 0;
}