#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXK 20

using namespace std;

// How many games can you win playing the respective move and having some swaps
int max_wins [3][MAXK + 1][MAXN + 1];
int fj_move[MAXN + 1];
int n, k;

bool wins(int a, int b)
{
    return (a + 1) % 3 == b;
}

int main(void)
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    scanf("%d %d", &n, &k);
    char c = getchar();
    for (int i = 0; i < n; i++) {
        c = getchar();
        if (c == 'H')
            fj_move[i+1] = 0;
        else if (c == 'S')
            fj_move[i+1] = 1;
        else 
            fj_move[i+1] = 2;
        getchar();
    }

    for (int x = 0; x < 3; x++) {
        // Max wins without swapping
        max_wins[x][0][0] = 0;
        for (int i = 1; i <= n; i++) {
            max_wins[x][0][i] = max_wins[x][0][i-1] + wins(x, fj_move[i]);
        }    
    }

    for (int s = 1; s <= k; s++) {
        // Max wins with s swaps
        for (int x = 0; x < 3; x++) {
            max_wins[x][s][0] = 0;

            for (int i = 1; i <= n; i++) {
                max_wins[x][s][i] = max_wins[x][s][i-1] + wins(x, fj_move[i]);

                int val = 0;
                for (int alter = 1; alter <= 2; alter++) {
                    int newmove = (x + alter) % 3;
                    val = max(val, max_wins[newmove][s-1][i-1] + wins(x, fj_move[i]));
                }
                max_wins[x][s][i] = max(max_wins[x][s][i], val);
            }
        }
    }

    int total_wins = 0;
    for (int x = 0; x < 3; x++) {
        total_wins = max(total_wins, max_wins[x][k][n]);
    }

    printf("%d\n", total_wins);
    return 0;
}