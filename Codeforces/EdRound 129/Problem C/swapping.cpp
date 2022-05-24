#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;
#define mp make_pair
#define pb push_back

unordered_map<int,int> start_a, ending_a, start_b, ending_b;
int a[100], b[100];
int good_a[100], good_b[100];
bool fixing[100];
vector<pair<int,int>> swaps;

bool overlap_ranges(int x1, int x2, int y1, int y2)
{
    if (x1 <= y2 && y1 <= x2)
        return true;
    
    return false;
}

ii find_overlap(int x1, int x2, int y1, int y2)
{
    return mp(max(x1, x2), min(y1, y2));
}

void swap_sort(int n)
{
    int need_fixing = n;
    for (int x = 0; x < n && need_fixing; x++) {
        for (int i = 0; i < n && need_fixing; i++) {
            if (!fixing[i]) {
                ii my_range = find_overlap(start_a[a[i]], start_b[b[i]], ending_a[a[i]], ending_b[b[i]]);
                if (i < my_range.first || i > my_range.second) {
                    int j = my_range.first;
                    bool done = false;
                    while(!done) {
                        if (!fixing[j]) {
                            swap(a[i], a[j]);
                            swap(b[i], b[i]);
                            swaps.pb(mp(i, j));

                            fixing[j] = true;
                            need_fixing--;
                            done = true;
                        }
                        else 
                            j++;
                    }
                }
                else {
                    fixing[i] = true;
                    need_fixing--;
                }
            }
        }
    }

    printf("%d\n", (int)swaps.size());
    for (auto x : swaps) {
        printf("%d %d\n", x.first + 1, x.second + 1);
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        start_a.clear();
        ending_a.clear();
        start_b.clear();
        ending_b.clear();
        swaps.clear();

        int n;
        scanf("%d", &n);
        memset(fixing, false, n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            good_a[i] = a[i];
        }
        for (int i = 0; i < n; i++) { 
            scanf("%d", &b[i]);
            good_b[i] = b[i];
        }

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

        //check for equal ranges
        bool isgood = true;
        for (int i = 0; i < n && isgood; i++) {
            if (!overlap_ranges(start_a[a[i]], ending_a[a[i]], start_b[b[i]], ending_b[b[i]]))
                isgood = false;
        }

        if (!isgood)
            printf("-1\n");
        else 
            swap_sort(n);
    }
}