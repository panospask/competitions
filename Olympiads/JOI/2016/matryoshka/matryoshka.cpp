#include <bits/stdc++.h>

using namespace std;

struct Doll {
    int r, h;

    void read(void) {
        scanf("%d %d", &r, &h);
    }
};
struct Query {
    int minR;
    int maxH;
    int id;

    void read(int i) {
        id = i;
        scanf("%d %d", &minR, &maxH);
    }
};

// A doll does NOT fit into another iff
// h_i < h_j AND r_i >= r_j
bool operator < (const Doll& a, const Doll& b)
{
    if (a.h == b.h) {
        return a.r > b.r;
    }
    return a.h < b.h;
}
bool operator < (const Query& a, const Query& b)
{
    return a.maxH < b.maxH;
}

int N, Q;
vector<Doll> dolls;
vector<Query> queries;
vector<int> ans;

// dp[i]: The highest R in each passage such that it is the i-th term
// in a nonincreasing subsequence
vector<int> dp;

// Returns the maximum position in the dp array such that dp[i] >= r
int calculate_position(int rad)
{
    int l = 0; //dp[l] >= r
    int r = N + 1; // dp[r] < r
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (dp[mid] >= rad) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    dolls.resize(N);
    queries.resize(Q);
    ans.resize(Q);

    for (int i = 0; i < N; i++) {
        dolls[i].read();
    }
    for (int i = 0; i < Q; i++) {
        queries[i].read(i);
    }

    sort(dolls.begin(), dolls.end());
    sort(queries.begin(), queries.end());

    dp.assign(N + 1, -1);
    dp[0] = INT_MAX;

    int q_p = 0;
    for (int i = 0; i < N; i++) {
        while (q_p < Q && queries[q_p].maxH < dolls[i].h) {
            ans[queries[q_p].id] = calculate_position(queries[q_p].minR);
            q_p++;
        }

        int res = calculate_position(dolls[i].r);
        dp[res + 1] = dolls[i].r;
    }
    while (q_p < Q) {
        ans[queries[q_p].id] = calculate_position(queries[q_p].minR);
        q_p++;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}