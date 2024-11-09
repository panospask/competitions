#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;

int pos;
vector<int> total;

struct Block {
    vector<int> positions;
    vector<int> values;
};

vector<int> rangequery(vector<int> v)
{
    int K = v.size();
    printf("2 %d", K);
    for (int i = 0; i < K; i++) {
        printf(" %d", v[i] + 1);
    }
    printf("\n");
    fflush(stdout);

    vector<int> res(K * (K - 1) / 2);
    for (int i = 0; i < res.size(); i++) {
        scanf("%d", &res[i]);
    }
    sort(res.begin(), res.end());

    return res;
}

// Returns abs(a[p[i]] - pos) for each i in random order
vector<int> differences(vector<int> p)
{
    if (p.size() == 1) {
        p.pb(pos);
        return rangequery(p);
    }

    int K = p.size();
    vector<int> res(K);

    vector<int> r1 = rangequery(p);
    p.pb(pos);
    vector<int> r2 = rangequery(p);

    int found = 0;
    for (int i = 0; i < r2.size(); i++) {
        if (r1[i - found] != r2[i]) {
            res[found] = r2[i];
            found++;
        }
    }

    return res;
}

bool contained(int val, vector<int>& v)
{
    int id = lower_bound(v.begin(), v.end(), val) - v.begin();
    if (id == v.size()) {
        return false;
    }

    return v[id] == val;
}

// Find the array c[i] = abs(a[p[i]] - pos)
vector<int> calculate(void)
{
    vector<Block> blocks;
    vector<Block> nxt;

    vector<int> ans(N);

    Block init;
    for (int i = 0; i < N; i++) {
        if (i == pos) {
            continue;
        }

        init.positions.pb(i);
    }
    init.values = differences(init.positions);

    blocks.pb(init);

    while (blocks.size()) {
        vector<int> query;

        for (auto [p, v] : blocks) {
            int len = p.size();

            if (len == 1) {
                ans[p[0]] = v[0];
                continue;
            }

            for (int i = 0; i < len / 2; i++) {
                query.pb(p[i]);
            }
        }

        if (query.empty()) {
            break;
        }
        vector<int> res = differences(query);

        for (auto [p, v] : blocks) {
            int len = p.size();

            if (len == 1) {
                continue;
            }

            Block n1, n2;
            for (int i = 0; i < len / 2; i++) {
                n1.positions.pb(p[i]);
            }
            for (int i = len / 2; i < len; i++) {
                n2.positions.pb(p[i]);
            }

            for (auto val : v) {
                if (contained(val, res)) {
                    n1.values.pb(val);
                }
                else {
                    n2.values.pb(val);
                }
            }

            nxt.pb(n1);
            nxt.pb(n2);
        }

        swap(blocks, nxt);
        nxt.clear();
    }

    return ans;
}

int max_in_range(int l, int r)
{
    vector<int> p;
    for (int i = l; i < r; i++) {
        p.pb(i);
    }

    vector<int> res = rangequery(p);

    if (res.empty()) {
        return 0;
    }
    return res.back();
}

int get(int i)
{
    printf("1 %d\n", i + 1);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

int main(void)
{
    scanf("%d", &N);

    if (N == 1) {
        int r = get(0);
        printf("3 %d\n", r);

        return 0;
    }

    // Find the position of either the minimum element or the maximum element
    int target = max_in_range(0, N);
    int l = 1;
    int r = N;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (max_in_range(0, mid) == target) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    pos = l;
    vector<int> b = calculate();

    vector<int> ans(N);
    int cmp = pos == 0 ? N - 1 : 0;
    
    ans[pos] = get(pos);
    ans[cmp] = get(cmp);

    int mod;
    if (ans[pos] < ans[cmp]) {
        mod = 1;
    }
    else {
        mod = -1;
    }

    for (int i = 0; i < N; i++) {
        if (i == pos) {
            continue;
        }

        ans[i] = ans[pos] + mod * b[i];
    }

    printf("3");
    for (int i = 0; i < N; i++) {
        printf(" %d", ans[i]);
    }
    printf("\n");
    fflush(stdout);

    return 0;
}