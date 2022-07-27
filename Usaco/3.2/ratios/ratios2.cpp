/*
ID: panos.p1
LANG: C++11
TASK: ratios
*/

#include <bits/stdc++.h>
#define mp make_pair
#define MAXN 100

using namespace std;

int mixtures[3][3];
int dp[MAXN + 5][MAXN + 5][MAXN + 5];
int goal[3];
int ansb = -1, anso, answ;
int ansdiv;

int main(void)
{
    freopen("ratios.in", "r", stdin);
    freopen("ratios.out", "w", stdout);
    
    scanf("%d %d %d", &goal[0], &goal[1], &goal[2]);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &mixtures[i][j]);

    int O, B, W;
    int bdiv, odiv, wdiv;
    for (int i = 0; i <= MAXN; i++)
        for (int j = 0; j <= MAXN; j++)
            for (int k = 0; k <= MAXN; k++) {
                B = mixtures[0][0] * i + mixtures[1][0] * j + mixtures[2][0] * k;
                O = mixtures[0][1] * i + mixtures[1][1] * j + mixtures[2][1] * k;
                W = mixtures[0][2] * i + mixtures[1][2] * j + mixtures[2][2] * k;

                // Barnley
                if (goal[0] == 0) {
                    if (B == 0)
                        bdiv = 0;
                    else 
                        bdiv = -1;
                }
                else if (B % goal[0] == 0 && B != 0)
                    bdiv = B / goal[0];
                else 
                    bdiv = -1;

                // Oats
                if (goal[1] == 0) {
                    if (O == 0)
                        odiv = 0;
                    else 
                        odiv = -1;
                }
                else if (O % goal[1] == 0 && O != 0)
                    odiv = O / goal[1];
                else 
                    odiv = -1;

                // Wheat
                if (goal[2] == 0) {
                    if (W == 0)
                        wdiv = 0;
                    else 
                        wdiv = -1;
                }
                else if (W % goal[2] == 0 && W != 0)
                    wdiv = W / goal[2];
                else 
                    wdiv = -1;

                if (wdiv != -1 && odiv != -1 && bdiv != -1) {
                    bool isgood = true;
                    int curdiv = bdiv;
                    if (curdiv == 0)
                        curdiv = odiv;
                    else 
                        if (odiv != curdiv && odiv != 0)
                            isgood = false;
                    if (curdiv == 0)
                        curdiv = wdiv;
                    else 
                        if (wdiv != curdiv && wdiv != 0)
                            isgood = false;
                    

                    if (isgood) {
                        if ((ansb == -1) || (i + j + k < ansb + anso + answ)) {
                            ansb = i;
                            anso = j;
                            answ = k;
                            ansdiv = curdiv;
                        }
                    }
                }
                
            }

    if (ansb == -1)
        printf("NONE\n");
    else 
        printf("%d %d %d %d\n", ansb, anso, answ, ansdiv);

    return 0;
}