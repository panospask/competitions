/*
ID: panos.p1
LANG: C++11
TASK: nuggets
*/

#include <bits/stdc++.h>
#define MAXNUM 2000000000
#define MAXOPT 10

using namespace std;
int nums[MAXOPT];
int n;
int max_undo = 0;
vector<bool> can_make;
int max_opt;

int main(void)
{
    freopen("nuggets.in", "r", stdin);
    freopen("nuggets.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums + n);
    max_opt = nums[n-1];

    int high = MAXNUM;
    int low = 1;
    int mid;
    int start;
    can_make.resize(max_opt + 5);
    while (high > low) {
        mid = (high + low) / 2;
        start = mid - mid % max_opt;

        bool found = false;
        for (int i = 0; i < n; i++) {
            ;
        }
    }
}