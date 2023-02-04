#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1500
#define MAXN 1500

using namespace std;

typedef pair<int, int> ii;

int n;
ii dir[MAXN + 2][MAXN + 2];
int depending_on[MAXN + 2][MAXN + 2];
int r[MAXN + 2];
int d[MAXN + 2];
int ttl_cost;

int main(void)
{
    // freopen("foldir.in", "r", stdin);
    // freopen("foldir.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char c = getchar();
        for (int j = 0; j < n; j++) {
            c = getchar();
            if (c == 'R')
                dir[i][j] = mp(0, 1);
            else 
                dir[i][j] = mp(1, 0);
            depending_on[i][j] = 1;        
        }
        scanf("%d", &r[i]);
    }
    for (int j = 0; j < n; j++)
        scanf("%d", &d[j]);

    //Calc total cost
    int next_i, next_j;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            tie(next_i, next_j) = mp(i + dir[i][j].first, j + dir[i][j].second);
            if (next_i == n) {
                ttl_cost += depending_on[i][j] * d[j];
            }
            else if (next_j == n) {
                ttl_cost += depending_on[i][j] * r[i];
            }
            else {
                depending_on[next_i][next_j] += depending_on[i][j];
            }
        }
    printf("%d\n", ttl_cost);

    int q;
    scanf("%d", &q);

    ii sqflip;
    ii old_dir;
    ii new_dir;
    for (int x = 0; x < q; x++) {
        scanf("%d %d", &sqflip.first, &sqflip.second);
        sqflip.first--;
        sqflip.second--;

        old_dir = dir[sqflip.first][sqflip.second];
        dir[sqflip.first][sqflip.second] = new_dir = mp(!(dir[sqflip.first][sqflip.second].first), !(dir[sqflip.first][sqflip.second].second));

        int i = sqflip.first, j = sqflip.second, next_i, next_j;
        while (true) {
            tie(next_i, next_j) = mp(i + dir[i][j].first, j + dir[i][j].second);
            if (next_j == n) {
                ttl_cost += depending_on[sqflip.first][sqflip.second] * r[i];
                break;
            }
            else if (next_i == n) {
                ttl_cost += depending_on[sqflip.first][sqflip.second] * d[j];
                break;
            }
            else {
                depending_on[next_i][next_j] += depending_on[sqflip.first][sqflip.second];
                i = next_i;
                j = next_j;
            }
        }

        // Remove the old ones
        i = sqflip.first; j = sqflip.second;
            dir[i][j] = old_dir;
            while(true) {
                tie(next_i, next_j) = mp(i + dir[i][j].first, j + dir[i][j].second);
                if (next_j == n) {
                    ttl_cost -= depending_on[sqflip.first][sqflip.second] * r[i];
                    break;
                }
                else if (next_i == n) {
                    ttl_cost -= depending_on[sqflip.first][sqflip.second] * d[j];
                    break;
                }
                else {
                    depending_on[next_i][next_j] -= depending_on[sqflip.first][sqflip.second];
                    i = next_i;
                    j = next_j;
                }
            }
            dir[sqflip.first][sqflip.second] = new_dir;

        printf("%d\n", ttl_cost);
    }

    return 0;
}