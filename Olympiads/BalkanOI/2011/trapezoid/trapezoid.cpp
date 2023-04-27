#include <bits/stdc++.h>
#define MOD 30013

using namespace std;

struct item {
    int num, oc;
};
typedef struct item Item;

Item IDENTITY = {INT_MIN, 0};
Item single(int a)
{
    Item i = {a, 1};
    return i;
}

Item merge(const Item& a, const Item& b)
{
    if (a.num == b.num)
        return {a.num, (a.oc + b.oc) % MOD};

    if (a.num > b.num)
        return a;
    else
        return b;
}

struct segtree {

    int size;
    vector<Item> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, IDENTITY);
    }

    void add(int i, Item v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = merge(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, Item v) {
        add(i, v, 0, 0, size);
    }

    Item get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return IDENTITY;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto it1 = get(l, r, 2 * x + 1, lx, mid);
        auto it2 = get(l, r, 2 * x + 2, mid, rx);

        return merge(it1, it2);
    }
    Item get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

struct trapezoidside {
    bool isfirst;
    int top, bottom;
    int id;

    bool operator < (trapezoidside& b) {
        return this->top < b.top;
    }
};
typedef struct trapezoidside TrapezoidSide;

int n;
vector<int> bottomcord;
vector<TrapezoidSide> sides;
vector<Item> best_cardinality;
segtree Avail_Trapezoids;

int getBottom(int x)
{
    return lower_bound(bottomcord.begin(), bottomcord.end(), x) - bottomcord.begin();
}

int main(void)
{
    scanf("%d", &n);
    sides.resize(2 * n);
    best_cardinality.resize(n);
    bottomcord.push_back(0);
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        sides[2 * i].top = a;
        sides[2 * i].bottom = c;
        sides[2 * i].isfirst = true;
        sides[2 * i].id = sides[2 * i + 1].id = i;
        sides[2 * i + 1].top = b;
        sides[2 * i + 1].bottom = d;
        sides[2 * i + 1].isfirst = false;

        bottomcord.push_back(c);
        bottomcord.push_back(d);
    }

    sort(bottomcord.begin(), bottomcord.end());
    sort(sides.begin(), sides.end());

    Avail_Trapezoids.init(bottomcord.size());
    Avail_Trapezoids.add(0, single(0));
    for (auto Side : sides) {
        if (Side.isfirst) {
            // Find the best cardinality with this trapezoid as the latest
            auto prev_card = Avail_Trapezoids.get(0, getBottom(Side.bottom) + 1);
            best_cardinality[Side.id].num = (prev_card.num + 1) % MOD;
            best_cardinality[Side.id].oc = prev_card.oc;
        }
        else {
            // This trapezoid can enter the available set
            Item card = best_cardinality[Side.id];
            Avail_Trapezoids.add(getBottom(Side.bottom), card);
        }
    }

    Item ans = Avail_Trapezoids.get(0, bottomcord.size());
    printf("%d %d\n", ans.num, ans.oc);
    return 0;
}