#include <bits/stdc++.h>
#define MAXN 100005
#define MAXR 350
// #define DEBUG

using namespace std;

// Using a pseudo-deque implementation

int prv[MAXN];
int nxt[MAXN];
int block[MAXN];
int cnt[MAXR][MAXN];
int arr[MAXN];
int start[MAXR];
int ending[MAXR];
int block_size;
int n, q;
int lastans = 0;
int w;
int c;

int decode(int i)
{
    return ((i + lastans - 1) % n) + 1;
}

void move_block_forward(int b)
{
    // Remove from one block...
    int last = ending[b];
    ending[b] = prv[last];
    nxt[prv[last]] = -1;
    cnt[b][arr[last]]--;

    //... and add to the other
    int first = start[b+1];
    nxt[last] = first;
    prv[first] = last;
    prv[last] = -1;
    start[b+1] = last;
    cnt[b + 1][arr[last]]++;

    if (ending[b+1] == -1 || ending[b+1] == -2)
        ending[b+1] = last;
}

void make_rotation(void)
{
    int temp_l, temp_r;

    scanf("%d %d", &temp_l, &temp_r);
    int l = decode(temp_l);
    int r = decode(temp_r);
    l--;
    r--;
    if (l > r)  swap(l, r);

    // Find r
    int rblock = r / block_size;
    int j = start[rblock];
    for (int i = rblock * block_size; i < r; i++)
        j = nxt[j];

    int rnum = j;

    // Find l
    int lblock = l / block_size;
    j = start[lblock];
    for (int i = lblock * block_size; i < l; i++)
        j = nxt[j];

    int lnum = j;

    if (lnum == rnum) return;

    if (rnum  < 0|| lnum < 0) {
        printf("WOOOOOOOOOOOOO in %d", w);
        exit(EXIT_FAILURE);
    }


    // Remove r from rblock
    if (ending[rblock] == rnum) {
        ending[rblock] = prv[rnum];
    }
    else {
        prv[nxt[rnum]] = prv[rnum];
    }
    if (start[rblock] == rnum) {
        start[rblock] = nxt[rnum];
    }
    else {
        nxt[prv[rnum]] = nxt[rnum];
    }
    cnt[rblock][arr[rnum]]--;
    
    // Add r to lblock
    nxt[rnum] = lnum;
    if (start[lblock] == lnum) {
        prv[rnum] = -1;
        start[lblock] = rnum;
    }
    else {
        nxt[prv[lnum]] = rnum;
        prv[rnum] = prv[lnum];
    }
    prv[lnum] = rnum;
    cnt[lblock][arr[rnum]]++;

    for (int i = lblock; i < rblock; i++)
        move_block_forward(i);
}

void find_num(void)
{
    int temp_l, temp_r, temp_k;

    scanf("%d %d %d", &temp_l, &temp_r, &temp_k);
    int l = decode(temp_l);
    int r = decode(temp_r);
    int k = decode(temp_k);
    r--;
    l--;
    if (l > r)  swap(l, r);

    // Find r
    int rblock = r / block_size;
    int j = start[rblock];
    for (int i = rblock * block_size; i < r; i++)
        j = nxt[j];

    int rnum = j;

    // Find l
    int lblock = l / block_size;
    j = start[lblock];
    for (int i = lblock * block_size; i < l; i++)
        j = nxt[j];

    int lnum = j;

    if (rnum  < 0|| lnum < 0) {
        printf("WOOOOOOOOOOOOO in %d", w);
        exit(EXIT_FAILURE);
    }


    int ttl_cnt = 0;
    int cur = lnum;
    while (cur != -1 && cur != -2) {
        ttl_cnt += arr[cur] == k;
        if (cur == rnum) break;
        cur = nxt[cur];
    }
    if (lblock != rblock) {
        cur = rnum;
        while (cur != -1 && cur != -2) {
            ttl_cnt += arr[cur] == k;
            cur = prv[cur];
        }
    }

    for (int i = lblock + 1; i < rblock; i++)
        ttl_cnt += cnt[i][k];

    printf("%d\n", ttl_cnt);
    lastans = ttl_cnt;
    return;
}

int main(void)
{
    #ifdef DEBUG
        freopen("260D.in", "r", stdin);
        freopen("260D.out", "w", stdout);
    #endif

    scanf("%d", &n);
    block_size = (int) sqrt(n);

    int curblock = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);

        if (i > 0) nxt[i-1] = i;
        prv[i] = i-1;
        if (i % block_size == 0) {
            curblock = i / block_size;
            start[curblock] = i;
            if (i > 0) ending[curblock-1] = i-1;
            if (i > 0) nxt[i-1] = -1;
            prv[i] = -1;
        }

        cnt[curblock][arr[i]]++;
    }
    prv[0] = -2;
    nxt[n-1] = -2;
    scanf("%d", &q);
    ending[curblock] = n-1;


    for (w = 0; w < q; w++) {
        scanf("%d", &c);
        if (c == 1)
            make_rotation();
        else 
            find_num();
    }

    return 0;
}