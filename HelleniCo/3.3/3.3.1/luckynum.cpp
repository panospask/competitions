#include <bits/stdc++.h>

using namespace std;

#define MAXN 2000000

int segtree[4 * MAXN + 5];
int elements_remaining;
int n;
bool deleted[MAXN + 5];

void build_tree(int ind, int from, int to)
{
    if (from == to) {
        segtree[ind] = 1;
        return;
    }

    int mid = (from + to) / 2;
    build_tree(2 * ind, from, mid);
    build_tree(2 * ind + 1, mid + 1, to);

    segtree[ind] = segtree[2 * ind] + segtree[2 * ind + 1];
}

int find_kth_element(int pos, int ind, int from = 1, int to = MAXN)
{
    if (from == to)
        return from;

    int mid = (from + to) / 2;

    if (segtree[2 * ind] >= pos)
        return find_kth_element(pos, 2 * ind, from, mid);
    else {
        return find_kth_element(pos - segtree[2 * ind], 2 * ind + 1, mid + 1, to);
    }
}

void remove_kth_element(int pos, int ind, int from = 1, int to = MAXN)
{
    if (from == to) {
        segtree[ind] = 0;
        elements_remaining--;
        deleted[from] = true;
        return;
    }

    int mid = (from + to) / 2;

    if (segtree[2 * ind] >= pos)
        remove_kth_element(pos, 2 * ind, from, mid);
    else 
        remove_kth_element(pos - segtree[2 * ind], 2 * ind + 1, mid + 1, to);

    segtree[ind] = segtree[2 * ind] + segtree[2 * ind + 1];
}

int main(void)
{
    freopen("luckynum.in", "r", stdin);
    freopen("luckynum.out", "w", stdout);

    scanf("%d", &n);
    elements_remaining = n;

    build_tree(1, 1, n);

    int i = 2;
    int k = 2;
    for (int j = 2; j < elements_remaining; j += 2 - 1)
        remove_kth_element(j, 1, 1, n);

    i = find_kth_element(k, 1, 1, n);

    while (true) {

        for (int j = i; j < elements_remaining; j += i - 1)
            remove_kth_element(j, 1, 1, n);

        k++;
        if (k > elements_remaining)
            break;
        i = find_kth_element(k, 1, 1, n);
    }

    for (int i = n / 2; i > 0; i--) {
        if (!deleted[i] && !deleted[n - i]) {
            printf("%d %d\n", i, n - i);
            break;
        }
    }

    return 0;
}