/*
ID: panos.p1
LANG: C++
TASK: beads
*/

#include <bits/stdc++.h>

using namespace std;

char necklace[1000];
bool used[1000];
int n;

int find_col(int i)
{
    int col;
    if (necklace[i] == 'b')
        col = 1;
    else if (necklace[i] == 'r')
        col = 2;
    else 
        col = 0;

    return col;
}

int explore_pos(int i)
{

    int col = find_col(i);
    bool decided = false;
    if (col != 0) {
        decided = true;
    }

    int cur_length = 1;
    int last_one = -1;
    for (int j = i + 1; j != i; j = (j + 1) % n) {
        j %= n;
        int cur_col = find_col(j);
        if (decided) {
            if (cur_col != 0 && cur_col != col) {
                last_one = j - 1;
                if (last_one == -1)
                    last_one = n - 1;
                break;
            }
            else 
                cur_length++;
        }
        else {
            if (cur_col != 0) {
                col = cur_col;
                decided = true;
            }

            cur_length++;
        }
    }

    if (last_one == -1)
        return cur_length;

    int ending = i - 1;
    if (ending == -1)
        ending = n -1;
    
    int rcol = find_col(ending);
    int rlength = 1;
    decided = false;
    if (rcol != 0)
        decided = true;

    for (int j = ending - 1; j != last_one; j--) {
        if (j == -1)
            j = n - 1;

        int cur_col = find_col(j);
        if (decided) {
            if (cur_col != 0 && cur_col != rcol) {
                break;
                last_one = j;
            }
            else 
                rlength++;
        }
        else {
            if (cur_col != 0) {
                rcol = cur_col;
                decided = true;
            }

            rlength++;
        }
    }


    return cur_length + rlength;
}

int main(void)
{
    freopen("beads.in", "r", stdin);
    freopen("beads.out", "w", stdout);

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        necklace[i] = getchar();
    }

    int max_length = 0;
    for (int i = 0; i < n; i++)
        max_length = max(max_length, explore_pos(i));


    printf("%d\n", max_length);
    return 0;
}