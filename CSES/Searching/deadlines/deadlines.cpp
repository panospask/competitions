#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

typedef pair<int, int> ii;

ii tasks[MAXN + 5];
int n;


int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &tasks[i].first, &tasks[i].second);
    }
    sort(tasks, tasks + n);

    long long int curtime = 0;
    long long int curscore = 0;
    for (int i = 0; i < n; i++) {
        curtime += tasks[i].first;
        curscore += tasks[i].second - curtime;
    }

    printf("%lld\n", curscore);
    return 0;
}