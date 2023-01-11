#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n, t;
int hunglevel[MAXN];

int main(void)
{
    // freopen("drought.in", "r", stdin);
    // freopen("drought.out", "w", stdout);

    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &hunglevel[i]);

        long long int corn_needed = 0;
        bool isgood = true;
        int to_change;
        int minval_in_check = INT_MAX;
        for (int i = 0; i < n - 1 && isgood; i++) {
            if (hunglevel[i] < 0) {
                isgood = false;
                break;
            }
            if (hunglevel[i] < hunglevel[i + 1]) {
                if (i != n -2) {
                    to_change = hunglevel[i + 1] - hunglevel[i];
                    hunglevel[i + 1] -= to_change;
                    hunglevel[i + 2] -= to_change;
                    corn_needed += 2 * to_change;
                }
                else {
                    isgood = false;
                    break;
                }
            }
            else if (hunglevel[i] > hunglevel[i + 1]) {
                if (i % 2) {
                    to_change = hunglevel[i] - hunglevel[i + 1];
                    corn_needed += (long long int)(i + 1) * to_change;
                    hunglevel[i] -= to_change;
                    minval_in_check -= to_change;
                }
                else {
                    isgood = false;
                    break;
                }
            }

            minval_in_check = min(minval_in_check, hunglevel[i]);
        }

        if (isgood && minval_in_check >= 0)
            printf("%lld\n", corn_needed);
        else 
            printf("-1\n");
    }
    return 0;
}