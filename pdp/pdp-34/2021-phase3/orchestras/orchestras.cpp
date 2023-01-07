/*
USER: 34pdppaskp
LANG: C++
TASK: orchestras
*/

#include <bits/stdc++.h>

using namespace std;

int compare_ints(const void* a,const void* b)
{
    return *(int*) a - *(int*) b;
}

int main(void)
{
    freopen("orchestras.in", "r", stdin);
    freopen("orchestras.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    int musicians[k][n];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &musicians[i][j]);

        sort(musicians[i], musicians[i] + n);
    }

    int max_diff = INT_MIN;
    for (int i = 0; i < n; i++) {
        int min = INT_MAX;
        int max = INT_MIN;
        for (int j = 0; j < k; j++) {
            if (musicians[j][i] > max)
                max = musicians[j][i];
            if (musicians[j][i] < min)
                min = musicians[j][i];
        }

        int diff = max - min;
        if (diff > max_diff)
            max_diff = diff;
    }

    cout << max_diff << endl;
}