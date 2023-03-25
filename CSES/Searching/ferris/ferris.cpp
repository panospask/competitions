#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, x ;
int weights[MAXN];

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);
    sort(weights, weights + n);

    int right_one = n - 1;
    int left_one = 0;
    int gondo_used = 0;
    while (right_one > left_one) {
        if (weights[left_one] + weights[right_one] <= x) {
            // Put both of them in a gondola together
            gondo_used++;
            left_one++;
            right_one--;
        }
        else {
            right_one--;
            gondo_used++;
        }
    }
    if (right_one == left_one)
        gondo_used++;

    printf("%d\n", gondo_used);
    return 0;
}