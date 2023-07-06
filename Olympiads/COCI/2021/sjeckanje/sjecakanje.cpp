#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    struct Node {
        ll f;
        ll l;

        // take first and last element or give to neighbours :]
        ll take[2][2];
    };

    int size;
    vector<ll> tree;

    ll total_val = 0;

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            ;
        }
    }
};

int main(void)
{
    ;
}