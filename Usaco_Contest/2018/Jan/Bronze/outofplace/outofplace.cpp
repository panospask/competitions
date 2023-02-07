#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int n;
int cowheight[MAXN];
int bessiespot = 0;
int bessiedir;

int first_of_x_height(int cow, int dir)
{
    int target = cowheight[cow];
    int ans = cow;
    for (int i = cow - 1; i >= 0; i += dir)
        if (cowheight[i] == target)
            ans = i;
        else 
            break;

    return ans;
}

bool is_order(int removed)
{
    int prevheight = cowheight[0];
    for (int i = 1; i < n; i++) {
        if (i == removed) continue;

        if (prevheight > cowheight[i])
            return false;
        prevheight = cowheight[i];
    } 

    return true;
}

int main(void)
{
    freopen("outofplace.in", "r", stdin);
    freopen("outofplace.out", "w", stdout);

    scanf("%d", &n);
    int prevh = -1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cowheight[i]);
    }

    // Find bessie
    for (int i = 1; i < n; i++) {
        if (cowheight[i - 1] > cowheight[i]) {
            // One of two cows is bessie
            
            // Check for order with the i-th cow removed
            if (is_order(i)) {
                bessiespot = i;
                bessiedir = -1;
            }
            else {
                bessiespot = i - 1;
                bessiedir = 1;
            }
        }
    }

    int swaps = 0;
    while (bessiespot + bessiedir >= 0 && bessiespot + bessiedir < n) {
        if (bessiedir == -1) {
            if (cowheight[bessiespot] < cowheight[bessiespot + bessiedir]) {
                int target = first_of_x_height(bessiespot + bessiedir, bessiedir);
                swap(cowheight[bessiespot], cowheight[target]);
                bessiespot = target;
                swaps++;
            }
            else 
                break;
        }   
        else {
            if (cowheight[bessiespot] > cowheight[bessiespot + bessiedir]) {
                int target = first_of_x_height(bessiespot + bessiedir, bessiedir);
                swap(cowheight[bessiespot], cowheight[target]);
                bessiespot = target;
                swaps++;
            }
            else 
                break;
        }
    }

    printf("%d\n", swaps);
    return 0;
}