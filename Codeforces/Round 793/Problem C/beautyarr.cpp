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
        for (int i = 0; i < n; i++)
            scanf("%d", &cur_arr[i]);
        
        int cur_b = ceil((float)n / 2);
        int rev_b = ceil((float)n / 2);

        for (int i = 0 ; i < n; i++) {
            counts[cur_arr[i]] = counts[cur_arr[i]] + 1;
            if (counts[cur_arr[i]] > 2) {
                if (counts[cur_arr[i]] % 2 == 1)
                    rev_b--;
                else 
                    cur_b--;
            }
        }

        if (n == 1)
            printf("1\n");
        else 
            printf("%d\n", min(cur_b, rev_b));
    }
}