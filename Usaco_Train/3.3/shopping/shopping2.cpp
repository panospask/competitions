/*
ID: panos.p1
LANG: C++11
TASK: shopping
*/

#include <bits/stdc++.h>
#define MAXIT 5

using namespace std;

typedef pair<int, int> ii;

struct offer {
    int size;
    int price;

    ii items[5];

    void readoffer(void) {
        scanf("%d", &size);
        for (int i = 0; i < size; i++)
            scanf("%d %d", &items[i].first, &items[i].second);
        scanf("%d", &price);
    }
};
typedef struct offer Offer;

int dp[MAXIT + 1][MAXIT + 1][MAXIT + 1][MAXIT + 1][MAXIT + 1];
map<int, int> code_to_num;
int offnum;
Offer offers[100];
int b;
int normprice[5];
int maxamount[5];

int find_num_in_offer(Offer& cur, int num)
{
    for (int i = 0; i < cur.size; i++)
        if (code_to_num[cur.items[i].first] == num)
            return cur.items[i].second;

    return 0;
}

void proccess_offer(Offer cur)
{
    int cnt[MAXIT];
    for (int i = 0; i < MAXIT; i++)
        cnt[i] = find_num_in_offer(cur, i + 1);

    for (int i = cnt[0]; i <= maxamount[0]; i++)
        for (int j = cnt[1]; j <= maxamount[1]; j++)
            for (int k = cnt[2]; k <= maxamount[2]; k++)
                for (int l = cnt[3]; l <= maxamount[3]; l++)
                    for (int m = cnt[4]; m <= maxamount[4]; m++) {
                        dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i-cnt[0]][j-cnt[1]][k-cnt[2]][l-cnt[3]][m-cnt[4]] + cur.price);
                    }
}

int main(void)
{
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);

    scanf("%d", &offnum);
    for (int i = 0; i < offnum; i++) {
        offers[i].readoffer();
    }
    scanf("%d", &b);
    int c, k, p;
    for (int i = 1; i <= b; i++) {
        scanf("%d %d %d", &c, &k, &p);
        code_to_num[c] = i;
        normprice[i-1] = p;
        maxamount[i-1] = k;
    }

    for (int i = b; i < MAXIT; i++) {
        normprice[i] = 0;
        maxamount[i] = 0;
    }

    for (int i = 0; i <= maxamount[0]; i++)
        for (int j = 0; j <= maxamount[1]; j++)
            for (int k = 0; k <= maxamount[2]; k++)
                for (int l = 0; l <= maxamount[3]; l++)
                    for (int m = 0; m <= maxamount[4]; m++)
                        dp[i][j][k][l][m] = i * normprice[0] + j * normprice[1] + k * normprice[2] + l * normprice[3] + m * normprice[4];

    for (int i = 0; i < offnum; i++)
        proccess_offer(offers[i]);

    int ans = dp[maxamount[0]][maxamount[1]][maxamount[2]][maxamount[3]][maxamount[4]];
    printf("%d\n", ans);
}