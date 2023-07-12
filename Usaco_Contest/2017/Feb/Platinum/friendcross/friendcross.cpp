#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = n;
        tree.resize(size, 0);
    }

    void add(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }

    int get(int i) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    int get(int l, int r) {
        return get(r - 1) - get(l - 1);
    }
};

struct Cow {
    int breed;
    int start;
    int end;
};
bool breedsort(const Cow& a, const Cow& b)
{
    return a.breed < b.breed;
}
bool startsort(const Cow& a, const Cow& b)
{
    return a.start < b.start;
}

int k, n;
BITree segments;
ll ans = 0;
vector<Cow> initial;

void calculate(vector<Cow>& cows)
{
    if (cows.size() == 1) {
        // No pairs
        return;
    }

    int mid = cows.size() / 2;
    vector<Cow> c1(mid), c2(cows.size() - mid);

    for (int i = 0; i < mid; i++)
        c1[i] = cows[i];
    for (int i = mid; i < cows.size(); i++)
        c2[i - mid] = cows[i];

    calculate(c1);
    calculate(c2);

    // All cow segments in c2 have starts further than the ones in c1
    // If they have shorter ends they form a nested pair :)
    sort(c1.begin(), c1.end(), breedsort);
    sort(c2.begin(), c2.end(), breedsort);

    int to_add = 0;
    for (auto cow : c2) {
        while (to_add < mid && c1[to_add].breed + k < cow.breed) {
            segments.add(c1[to_add].end, 1);
            to_add++;
        }

        ans += segments.get(cow.end, 2 * n);
    }
    while (to_add > 0) {
        segments.add(c1[to_add - 1].end, -1);
        to_add--;
    }

    reverse(c1.begin(), c1.end());
    reverse(c2.begin(), c2.end());

    to_add = 0;
    for (auto cow : c2) {
        while (to_add < mid && c1[to_add].breed - k > cow.breed) {
            segments.add(c1[to_add].end, 1);
            to_add++;
        }

        ans += segments.get(cow.end, 2 * n);
    }
    while (to_add > 0) {
        segments.add(c1[to_add - 1].end, -1);
        to_add--;
    }

    return;
}

int main(void)
{
    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);

    scanf("%d %d", &n, &k);
    initial.resize(n);
    for (int i = 0; i < n; i++) {
        int b;
        scanf("%d", &b);
        b--;

        initial[b].breed = b;
        initial[b].start = i;
    }
    for (int i = n; i < 2 * n; i++) {
        int b;
        scanf("%d", &b);
        b--;

        initial[b].end = i;
    }
    segments.init(2 * n);

    sort(initial.begin(), initial.end(), startsort);
    calculate(initial);

    printf("%lld\n", ans);

    return 0;
}