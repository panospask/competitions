#include <bits/stdc++.h>

using namespace std;

int n, m;
int table[10000][10000];
int cor_table[10000][10000];
bool have_sw;
int ans;
pair<int,int> the_swap;

int comp_ints(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void swap_cols(int i, int j)
{
    for (int x = 0; x < n; x++)
        swap(table[x][i], table[x][j]);
}

bool iterate_rows(void)
{
    ans = 2;
    for (int i = 0; i < n && ans == 2; i++) {
        qsort(cor_table[i], m, sizeof(int), comp_ints);

        int find_i_swap = INT_MAX;
        for (int j = 0; j < m; j++) {
            if (table[i] != cor_table[i]) {
                if (!have_sw) {
                    if (find_i_swap != INT_MAX) {
                        if (table[find_i_swap] == cor_table[i]) {
                            have_sw = false;
                            swap_cols(i, find_i_swap);
                            ans = iterate_rows();
                            the_swap.first = i;
                            the_swap.second = find_i_swap;
                            break;
                        }
                        else {
                            ans = false;
                            break;
                        }
                    }
                }
                else {
                    ans = false;
                    break;
                }
            }
            else {
                ans = 2;
            }
        }
    }

    return ans;
}


int main(void)
{
    int t;
    for (int x = 0; x < t; x++) {
        have_sw = false;
        ans = 2;
        the_swap.first = -1;
        the_swap.second = -1;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                scanf("%d", &table[i][j]);
                cor_table[i][j] = table[i][j];
            }


        if (!ans)
            printf("-1\n");
        else {
            if (the_swap.first == -1)
                printf("1 1\n");
            else {
                printf("%d %d\n", the_swap.first + 1, the_swap.second + 1);
            }
        }
        
    }
}