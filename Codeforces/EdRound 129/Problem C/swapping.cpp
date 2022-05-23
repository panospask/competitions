#include <bits/stdc++.h>

using namespace std;

unordered_map<int,int> start_a, ending_a, start_b, ending_b, is_in;
int a[100], b[100];
int cur_spot[100];
int good_a[100], good_b[100];
bool fixing[100];
pair<int,int> swaps[150];

bool overlap_ranges(int x1, int x2, int y1, int y2)
{
    if (x1 <= y2 && y1 <= x2)
        return true;
    
    return false;
}

void selection_sort(void)
{
    ;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        is_in.clear();
        start_a.clear();
        ending_a.clear();
        start_b.clear();
        ending_b.clear();

        int n;
        scanf("%d", &n);
        memset(fixing, false, n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            cur_spot[i] = i;
            is_in[i] = i;
        }
        for (int i = 0; i < n; i++) 
            scanf("%d", &b[i]);

        sort(good_a, good_a + n);
        sort(good_b, good_b + n);

        int prev_num = -1;
        for (int i = 0; i < n; i++) {
            if (good_a[i] != prev_num) {
                ending_a[prev_num] = i - 1;
                start_a[good_a[i]] = i;
                prev_num = good_a[i];
            }
        }
        ending_a[prev_num] = n - 1;
        prev_num = -1;
        for (int i = 0; i < n; i++) {
            if (good_b[i] != prev_num) {
                ending_b[prev_num] = i - 1;
                start_b[good_b[i]] = i;
                prev_num = good_b[i];
            }
        }
        ending_b[prev_num] = n - 1;

        bool is_good = true;
        int swap_num = 0;
        for (int i = 0; i < n && is_good; i++) {
            if (!overlap_ranges(start_a[a[cur_spot[i]]], ending_a[a[cur_spot[i]]], start_b[b[cur_spot[i]]], ending_b[b[cur_spot[i]]])) 
                is_good = false;
            else {
                for (int j = max(start_a[a[cur_spot[i]]], start_b[b[cur_spot[i]]]); j <= min(ending_a[a[cur_spot[i]]], ending_b[b[cur_spot[i]]]); j++) {
                    if (!fixing[j]) {
                        fixing[j] = true;
                        if (cur_spot[i] != j) {
                        swaps[swap_num].first = cur_spot[i];
                        swaps[swap_num].second = j;
                        swap(a[cur_spot[i]], a[j]);
                        swap(b[cur_spot[i]], b[j]);
                        int temp = cur_spot[is_in[j]];
                        cur_spot[is_in[j]] = cur_spot[i];
                        cur_spot[i] = j;
                        is_in[i] = is_in[j];
                        is_in[j] = i; // Not totally correct

                        }
                        else 
                            swap_num--;
                        
                        break;
                    }
                }
                swap_num++;
            }
        }

        if (is_good) {
            int new_swap = swap_num;
            for (int i = 0; i < swap_num; i++) {
                if (swaps[i].first == swaps[i].second) {
                    new_swap--;
                    swaps[i].first = -1;
                }
            }   

            printf("%d\n", new_swap);
            for (int i = 0 ; i < swap_num; i++) {
                if (swaps[i].first != -1)
                    printf("%d %d\n", swaps[i].first, swaps[i].second);
            }
        }
        else 
            printf("-1\n");
    }
}