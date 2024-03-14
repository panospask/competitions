#include <bits/stdc++.h>

using namespace std;

int n, a[50005], b[50005];
bool smaller = false;

int find_max_diff(void)
{
    int diff = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            smaller = true;
            break;
        }
        else {
            if (a[i] - b[i] > a[diff] - b[diff])
                diff = i;
        }
    }

    return diff;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    
    for (int x = 0; x < t; x++) {
        smaller = false;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) 
            scanf("%d", &a[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &b[i]);

        int diff_num = find_max_diff();

        if (!smaller) {
            int differ = a[diff_num] - b[diff_num];
            for (int i = 0; i < n && !smaller; i++) {
                if (a[i] - b[i] != differ && b[i] != 0) {
                    smaller = true;
                    break;
                }
            }
        }

        if (smaller)
            printf("NO\n");
        else 
            printf("YES\n");
    }

    return 0;
}