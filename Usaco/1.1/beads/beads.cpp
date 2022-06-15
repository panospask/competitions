/*
ID: panos.p1
LANG: C++
TASK: beads
*/

#include <bits/stdc++.h>

using namespace std;

char necklace[355];

int main(void)
{
    freopen("beads.in", "r", stdin);
    freopen("beads.out", "w", stdout);

    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        necklace[i] = getchar();
    }

    int max_length = 0;
    int cur_length = 0;
    int cur_col = 1;
    int latest_non_w = -1;
    bool has_started = false;

    for (int i = 0; i < n; i++) {
        int col;
        if (necklace[i] == 'b')
            col = 1;
        else if (necklace[i] == 'r')
            col = 2;
        else 
            col = 0;

        if (has_started) {
            if (col == cur_col || col == 0) {
                cur_length++;
                if (col == cur_col)
                    latest_non_w = i;
            }
            else {
                max_length = max(cur_length, max_length);
                cur_col = col;
                cur_length = i - latest_non_w;
                latest_non_w = i;
            }
        }
        else {
            if (col != 0) {
                cur_length = i + 1;
                latest_non_w = i;
                cur_col = col;
                has_started = true;
            }
        }
    }

    printf("%d\n", max_length);
}