#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(10e5)

using namespace std;

int cowval[MAXN];
int n;
int total_sum;

bool try_mod(int modnum)
{
    int elements_remaining = n - modnum;

    // Make sure that it's an integer number
    if (total_sum % elements_remaining)
        return false;
    
    int goal = total_sum / elements_remaining;
    int curval = 0;
    for (int i = 0; i < n; i++) {
        curval += cowval[i];
        if (curval == goal)
            curval = 0;
        else if (curval > goal)
            return false;
    }

    return true;
}

int main(void)
{
    // freopen("sleeping.in", "r", stdin);
    // freopen("sleeping.out", "w", stdout);

    int t;
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        total_sum = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &cowval[i]);
            total_sum += cowval[i];
        }

        for (int j = 0; j < n; j++)
            if ( total_sum % (n - j) == 0) {
                if (try_mod(j)) {
                    printf("%d\n", j);
                    break;
                }
            }        
    }
    return 0;
}