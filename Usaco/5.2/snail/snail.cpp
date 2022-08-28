/*
ID: panos.p1
LANG: C++11
TASK: snail
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 150
#define MOD(i, j) (((i % j) + j) % j)

using namespace std;

typedef pair<int, int> ii;

int image[MAXN][MAXN];
bool visited[MAXN][MAXN];
int n, b;
int cursquares;
int idir[] = {1, 0, -1, 0};
int jdir[] = {0, 1, 0, -1};
int ans;

bool can_turn(int i, int j)
{
    return (i < 0 || i >= n || j < 0 || j >= n || image[i][j]); 
}

bool blocked(int i, int j)
{
    return (i < 0 || i >= n || j < 0 || j >= n || visited[i][j] || image[i][j]); 
}

void dfs(int i, int j, int curdir)
{
    int start_i = i, start_j = j;
    i += idir[curdir];
    j += jdir[curdir];

    if  (blocked(i, j)) {
        // Terminate
        ans = max(ans, cursquares);
        return;
    }

    while (!blocked(i, j)) {
        cursquares++;
        visited[i][j] = true;
        i += idir[curdir];
        j += jdir[curdir];
    }

    if (can_turn(i, j)) {
        i -= idir[curdir];
        j -= jdir[curdir];
        dfs(i, j, MOD(curdir - 1, 4));
        dfs(i, j, MOD(curdir + 1, 4));
    }
    else {
        i -= idir[curdir];
        j -= jdir[curdir];
        ans = max(ans, cursquares);
    }

    while (i != start_i || j != start_j) {
        visited[i][j] = false;
        i -= idir[curdir];
        j -= jdir[curdir];
        cursquares--;
    }

    return;
}

int main(void)
{
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);

    scanf("%d %d", &n, &b);
    char column;
    int row; 
    for (int i = 0; i < b; i++) {
        getchar();
        scanf("%c %d", &column, &row);
        image[row - 1][column - 'A'] = 1;
    }

    cursquares = 0;
    cursquares++;

    dfs(0, 0, 0);
    dfs(0, 0, 1);    

    printf("%d\n", ans);
    return 0;
}