#include <bits/stdc++.h>
#define MAXN 100005
// #define DEBUG

using namespace std;

int next_block_land[MAXN];
int powr[MAXN];
int cnt[MAXN];
int block_size;
int n, m;

void change_powr(void)
{
    int a, b;
    scanf("%d %d", &a, &b);
    a--;

    powr[a] = b;
    for (int i = a; i / block_size == a / block_size && i >= 0; i--) {
        if (i + powr[i] >= n) {
            next_block_land[i] = -1;
            cnt[i] = 1;
        }

        else if ((i + powr[i]) / block_size > i / block_size) {
            next_block_land[i] = i + powr[i];
            cnt[i] = 1;
        }
        else {
            next_block_land[i] = next_block_land[i + powr[i]];
            cnt[i] = cnt[i + powr[i]] + 1;
        }
    }
}
void query(void)
{
    int a;
    scanf("%d", &a);
    a--;

    int ttl_cnt = 0;
    int preva;
    while (a != -1) {
        ttl_cnt += cnt[a];
        preva = a;
        a = next_block_land[a];
    }

    while (powr[preva] + preva < n)
        preva += powr[preva];

    printf("%d %d\n", preva + 1, ttl_cnt);
}

int main(void)
{
    #ifdef DEBUG
        freopen("13E.in", "r", stdin);
        freopen("13E.out", "w", stdout);
    #endif

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &powr[i]);

    block_size = (int)sqrt(n);

    for (int i = n - 1; i >= 0; i--) {
        if (powr[i] + i >= n) {
            next_block_land[i] = -1;
            cnt[i] = 1;
        }
        else if ((powr[i] + i) / block_size > i / block_size) {
            next_block_land[i] = powr[i] + i;
            cnt[i] = 1;
        }
        else {
            next_block_land[i] = next_block_land[i + powr[i]];
            cnt[i] = cnt[i + powr[i]] + 1;
        }
    }

    int type;
    for (int x = 0; x < m; x++) {
        scanf("%d", &type);

        if (type == 0)
            change_powr();
        else 
            query();
    }

    return 0;
}