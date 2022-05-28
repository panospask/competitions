#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n, q;
    scanf("%d %d", &n, &q);

    int startarray[n];

    long long int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &startarray[i]);
        sum += startarray[i];
    }

    bool changednum[n] = {false};
    bool have_changed = false;
    int new_change = -1;

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int num, val;
            if (have_changed) {
                ;
            }
            else {
                sum -= startarray[num];
                startarray[num] = val;
                sum += startarray[num];
            }
        }
    }
}