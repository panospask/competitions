/*
ID: panos.p1
LANG: C++11
TASK: twofive
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHAR_PER_ROW 5
#define ROWS 5
#define N (ROWS * CHAR_PER_ROW)

using namespace std;

int dp[CHAR_PER_ROW + 1][CHAR_PER_ROW + 1][CHAR_PER_ROW + 1][CHAR_PER_ROW + 1][CHAR_PER_ROW + 1];
int columns[ROWS];
string tmp(CHAR_PER_ROW * ROWS, ' ');

int count_with(char c)
{
    if (dp[columns[0]][columns[1]][columns[2]][columns[3]][columns[4]])
        return dp[columns[0]][columns[1]][columns[2]][columns[3]][columns[4]];

    int ttl = 0;
    for (int i = 0; i < ROWS; i++) {
        if ((i == 0 && columns[i] < 5) || columns[i] < columns[i-1]) 
            if (tmp[columns[i] + CHAR_PER_ROW * i] == ' ' || tmp[columns[i] + CHAR_PER_ROW * i] == c) {
                columns[i]++;
                ttl += count_with(c + 1); // Always place the next largest letter next
                columns[i]--;
            }
    }

    return dp[columns[0]][columns[1]][columns[2]][columns[3]][columns[4]] = ttl;
}

int main(void)
{
    freopen("twofive.in", "r", stdin);
    freopen("twofive.out", "w", stdout);

    char type = getchar();

    if (type == 'W') {
        string q;
        cin >> q;

        int ttl_before = 0;

        for (int i = 0; i < N; i++) { //Count the smaller strings whose difference to q begins at i
            for (char a = 'A'; a < q[i]; a++) {
                tmp[i] = a;
                memset(columns, 0, sizeof(columns));
                memset(dp, 0, sizeof(dp));
                dp[5][5][5][5][5] = 1; // When all 5 rows have been filled, only 1 possibility remains

                ttl_before += count_with('A');
            }
            tmp[i] = q[i];
        }

        printf("%d\n", ttl_before + 1);
    }
    else {
        int pos;
        scanf("%d", &pos);
        int ttl_before = 0;
        int cur_total;

        for (int i = 0; i < N; i++)
            for (char a = 'A'; a <= 'Y'; a++) {
                tmp[i] = a;
                memset(columns, 0, sizeof(columns));
                memset(dp, 0, sizeof(dp));
                dp[5][5][5][5][5] = 1;

                cur_total = count_with('A');
                if (ttl_before + cur_total >= pos)
                    break;
                else 
                    ttl_before += cur_total;
            }

        cout << tmp << '\n';
    }

    return 0;
}