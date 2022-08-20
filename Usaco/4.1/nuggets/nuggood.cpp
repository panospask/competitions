/*
ID: panos.p1
LANG: C++11
TASK: nuggets
*/

#include <bits/stdc++.h>

using namespace std;

int n;
int nums[10];
bool curdp[256];
bool prevdp[256];
int maxno;
int mino;
int curstreak;
int prevstreak = 0;
bool ending = false;
int curit = 0;
int ans;

int main(void)
{
    freopen("nuggets.in", "r", stdin);
    freopen("nuggets.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums + n);
    maxno = nums[n-1];
    int minno = nums[0];
    curstreak = 0;

    //Initialize prevdp
    for (int i = 0; i < maxno; i++)
        prevdp[i] = false;
    curit = 0;

    while (!ending) {
        curstreak = 0;
        memset(curdp, false, sizeof(curdp));
        curdp[0] = true;
        for (int i = 0; i < n - 1; i++) {
            int curnum = nums[i];
            // Find from prev:
            for (int j = maxno - curnum + 1; j < maxno; j++) {
                curdp[j + curnum - maxno] = (curdp[j + curnum - maxno] || prevdp[j]);
            }
            // Find from cur:
            for (int j = 0; j < maxno - curnum; j++) {
                curdp[j + curnum] = (curdp[j + curnum] || curdp[j]);
            }
        }
        // Check the streak
            for (int j = 0; j < maxno; j++) {
                if (curdp[j]) {
                    curstreak++;
                }
                else {
                    ans = j + curit * maxno;
                }
                prevdp[j] = curdp[j];
            }
            if (curstreak >= maxno)
                ending = true;
            else if (curstreak == prevstreak) {
                ans = 0; 
                ending = true;
            }
            curit++;
            prevstreak = curstreak;
    }

    printf("%d\n", ans);
    return 0;
}