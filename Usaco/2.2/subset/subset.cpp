/*
ID: panos.p1
LANG: C++
TASK: subset
*/

#include <bits/stdc++.h>

using namespace std;

int n;
int occurances = 0;
bool visited[40];
int sum_made;

void dfs(int i, int s, int last)
{


    if (s == sum_made) {
        occurances++;
        return;
    }
    if (s > sum_made)
        return;

    if (last == n + 1)
        return;

    for (int j = last + 1; j <= n; j++)
        if (!visited[j]) {
            visited[j] = true;

            dfs(i - 1, s + j, j);

            visited[j] = false;
        }
    return;
}

int main(void)
{
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);

    scanf("%d", &n);

    sum_made = (n * (n + 1)) / 2;
    if (sum_made % 2 == 1) {
        printf("%d\n", 0);
        return 0;
    }

    sum_made /= 2;

    dfs(n, 0, 0);

    occurances /= 2;

    printf("%d\n", occurances);
    return 0;
}