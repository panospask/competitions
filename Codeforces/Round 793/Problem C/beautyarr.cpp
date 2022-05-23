#include <bits/stdc++.h>

using namespace std;

map<int,int> counts;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        counts.clear();
        int n;
        scanf("%d", &n);

        int cur_arr[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &cur_arr[i]);
            counts[i]++;
        }
        
        int singles = 0, dobles = 0;
        for (auto j : counts) {
            singles += j.second == 1;
            dobles += j.second > 1;
        }

        printf("%d\n", dobles + (singles) / 2);
    }

    return 0;
}