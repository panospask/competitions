#include <bits/stdc++.h>

using namespace std;

struct query {
    int l, r;
    int id;
};
typedef struct query Query;

const int IDENTITY = INT_MAX;

vector<int> lefty;
vector<int> righty;
int n, q;
vector<int> a;
vector<int> ans;
vector<Query> init;

void divide(int lx, int rx, vector<int>& queries)
{
    if (!queries.size()) return;
    if (lx == rx - 1) {
        for (auto q : queries)
            ans[q] = a[lx];

        return;
    }

    int mid = (lx + rx) / 2;

    int prv = IDENTITY;
    for (int i = mid - 1; i >= lx; i--) {
        lefty[i] = min(a[i], prv);
        prv = lefty[i];
    }

    righty.resize(rx);
    prv = IDENTITY;
    for (int i = mid; i < rx; i++) {
        righty[i] = min(a[i], prv);
        prv = righty[i];
    }

    vector<int> q1, q2;
    for (auto& q : queries) {
        if (init[q].l < mid) {
            if (init[q].r <= mid)
                q1.push_back(q);
            else
                ans[q] = min(lefty[init[q].l], righty[init[q].r - 1]);
        }
        else {
            q2.push_back(q);
        }
    }

    divide(lx, mid, q1);
    divide(mid, rx, q2);
}

int main(void)
{
    scanf("%d %d", &n, &q);
    vector<int> starting;
    starting.resize(q);
    init.resize(q);
    a.resize(n);
    ans.resize(q);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &init[i].l, &init[i].r);
        init[i].l--;
        starting[i] = i;
        init[i].id = i;
    }
    lefty.resize(n);
    righty.resize(n);

    divide(0, n, starting);
    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}