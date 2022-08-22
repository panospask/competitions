#include <bits/stdc++.h>
#define MAXN 100005
#define mp make_pair

using namespace std;

struct query {
    int l;
    int r;
    int order;
};
typedef struct query Query;

int block_num;
int n, m;
int freq[MAXN];
int arr[MAXN];
Query lst[MAXN];
int ans = 0;
int answr[MAXN];

bool operator <(Query a, Query b)
{
    if (a.l / block_num == b.l / block_num)
        return a.r < b.r;
    
    return a.l / block_num < b.l / block_num;
}

void move_end_from_to(int a, int b)
{
    int cur;
    if (a < b) {
        for (int i = a + 1; i <= b; i++) {
            if (i < 0) continue;
            cur = arr[i];
            if (cur > n) continue;
            freq[cur]++;
            if (freq[cur] == cur)
                ans++;
            else if (freq[cur] == cur + 1)
                ans--;
        }
    }
    if (a > b) {
        for (int i = a; i > b; i--) {
            if (i < 0) continue;
            cur = arr[i];
            if (cur > n) continue;
            freq[cur]--;
            if (freq[cur] == cur)
                ans++;
            else if (freq[cur] == cur - 1)
                ans--;
        }
    }
}

void move_start_from_to(int a, int b)
{
    int cur;
    if (a < b) {
        for (int i = a; i < b; i++) {
            if (i < 0) continue;
            cur = arr[i];
            if (cur > n) continue;
            freq[cur]--;
            if (freq[cur] == cur)
                ans++;
            else if (freq[cur] == cur - 1)
                ans--;
        }
    }
    if (a > b) {
        for (int i = a - 1; i >= b; i--) {
            if (i < 0) continue;
            cur = arr[i];
            if (cur > n) continue;
            freq[cur]++;
            if (freq[cur] == cur)
                ans++;
            else if (freq[cur] == cur + 1)
                ans--;
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);

    block_num = (int) sqrt(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &lst[i].l, &lst[i].r);
        lst[i].l--;
        lst[i].r--;
        lst[i].order = i;
    }
    sort(lst, lst + m);

    int cur_block = 0, cur_l = -1, cur_r = -1;
    Query cur_q;
    for (int x = 0; x < m; x++) {
        cur_q = lst[x];
        move_start_from_to(cur_l, lst[x].l);
        move_end_from_to(cur_r, lst[x].r);
        cur_l = lst[x].l;
        cur_r = lst[x].r;

        answr[lst[x].order] = ans;
    }

    for (int x = 0; x < m; x++) {
        printf("%d\n", answr[x]);
    }
    return 0;
}