#include <bits/stdc++.h>
#define MAXN 200000
#define MAXX 1000000

using namespace std;

int MAXDIV = sqrt(MAXX);

int nums[MAXN + 2];
int n;
int have_value[MAXX + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        
        have_value[nums[i]]++;
    }

    int ans = 1;
    for (int i = 2; i <= MAXX; i++) {
        int curval = 0;
        for (int x = i; x <= MAXX; x += i)
            curval += have_value[x];

        if (curval >= 2)
            ans = i;
    }

    printf("%d\n", ans);
    return 0;
}