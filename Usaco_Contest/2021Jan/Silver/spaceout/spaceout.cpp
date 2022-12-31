#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

int n;
int beautyval[MAXN + 2][MAXN + 2];
int sum[2];

int main(void)
{
    // freopen("spaceout.in", "r", stdin);
    // freopen("spaceout.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &beautyval[i][j]);

    // Max beauty if every col alternates between cow and no cow
    int colsum = 0;

    // Max beauty if every row alternates between cow and no cow
    int rowsum = 0;

    for (int i = 0; i < n; i++) {
        //If each row has an alternating pattern of cow, no cow
        memset(sum, 0, sizeof(sum));

        for (int j = 0; j < n; j++) 
            sum[j % 2] += beautyval[i][j];

        // Add the maximum of the odd/even places to the total sum
        rowsum += max(sum[0], sum[1]);
    }
    for (int j = 0; j < n; j++) {
        // If each column  has an alternating pattern of cow, now cow
        memset(sum, 0, sizeof(sum));

        for (int i = 0; i < n; i++)
            sum[i % 2] += beautyval[i][j];

        // Add the maximum of the odd/even places to the total sum
        colsum += max(sum[0], sum[1]);
    }

    printf("%d\n", max(rowsum, colsum));
    return 0;
}