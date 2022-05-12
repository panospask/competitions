#include <bits/stdc++.h>

using namespace std;

long seg_tree[1050003];
long final_rank[500001];
long n;

void init_seg_tree(long i, long b, long e)
{
    if (b == e) {
        seg_tree[i] = 1;
        return;
    }
    
    long mid = (b + e) / 2;
    init_seg_tree(i * 2, b, mid);
    init_seg_tree(i * 2 + 1, mid + 1, e);
    seg_tree[i] = seg_tree[i * 2] + seg_tree[i * 2 + 1];
}

void find_min_space(long a, long segment_tree[], long num)
{
    long first = 1, last = n, node = 1;

    while (first != last) {
        segment_tree[node]--;
        long mid = (first + last) / 2;
        if (segment_tree[2 * node] >= a) {
            last = mid;
            node = 2 * node;
        }
        else {
            a -= segment_tree[2 * node];
            node = 2 * node + 1;
            first = mid + 1;
        }
    }
    segment_tree[node]--;

    final_rank[first] = num;
}

int main(void)
{
    freopen("rafting.in", "r", stdin);
    freopen("rafting.out", "w", stdout);

    cin >> n;

    long rank[n + 1];
    for (long i = 1; i <= n; i++) {
        scanf("%ld", &rank[i]);
    }

    init_seg_tree(1, 1, n);

    for (long i = n; i >= 1; i--) {
        find_min_space(rank[i], seg_tree, i);
    }

    for (long i = 1; i <= n; i++) 
        printf("%ld ", final_rank[i]);
    
    cout << endl;
}