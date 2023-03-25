#include <bits/stdc++.h>
#define MAXN 5000

using namespace std;

typedef pair<int, int> ii;

int n, x;
int a[MAXN];
bool used_sort[MAXN];
bool used_norm[MAXN];
int sorted_a[MAXN];

int find_in_or(int val)
{
    for (int i = 0; i < n; i++)
        if (!used_norm[i] && a[i] == val) {
            used_norm[i] = true;
            return i;
        }

    return -1;
}

ii two_sum(int sum_needed)
{
    int l = 0, r = n - 1;
    bool found = false;
    ii ans = make_pair(-1, -1);

    while (l < r && !found) {
        while (sorted_a[l] + sorted_a[r] > sum_needed || used_sort[r])
            r--;

        if (l >= r)
            break;

        if (sorted_a[l] + sorted_a[r] == sum_needed) {
            found = true;
            ans = make_pair(find_in_or(sorted_a[l]), find_in_or(sorted_a[r]));
        }

        l++;
        while (used_sort[l]) l++;
    }


    return ans;
}

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sorted_a[i] = a[i];
    }

    sort(sorted_a, sorted_a + n);

    ii two_ans;
    int curans = -1;
    int cur_remove;

    for (int i = 0; i < n; i++) {
        // Pick a value from a and then execute twosum in sorted_a
        for (int j = 0; j < n; j++)
            if (sorted_a[j] == a[i]) { 
                used_sort[j] = true;
                used_norm[i] = true;
                cur_remove = j;
                break;
            }

        two_ans = two_sum(x - a[i]);
        if (two_ans.first != -1) {
            curans = i;
            break;
        }

        used_sort[cur_remove] = false;
        used_norm[i] = false;
    }

    if (curans == -1)
        printf("IMPOSSIBLE\n");
    else 
        printf("%d %d %d", curans + 1, two_ans.first + 1, two_ans.second + 1);
}