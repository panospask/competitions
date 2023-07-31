#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

typedef pair<int, int> pi;

struct Doll {
    int diameter;
    int height;
};
bool operator < (const Doll& a, const Doll& b)
{
    if (a.height == b.height)
        return a.diameter > b.diameter;
    return a.height < b.height;
}

int N, Q;
vector<Doll> dolls;
vector<pair<pi, int>> queries;
// dp[i]: Maximum diameter of matryoshka doll at each time step
vector<int> dp;
vector<int> ans;

bool gcomp(const int& a, const int& b)
{
    return a > b;
}

void process_query(int v)
{
    // Only take dolls with diameter as required
    int res = upper_bound(dp.begin(), dp.end(), queries[v].first.first, gcomp) - dp.begin();

    // All dolls at position res and above have diameter smaller than required queries[cur_]

    ans[queries[v].second] = res - 1;
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    dolls.resize(N);
    queries.resize(Q);
    ans.resize(Q);
    dp.resize(N + 1, 0);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &dolls[i].diameter, &dolls[i].height);
    }
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &queries[i].first.first, &queries[i].first.second);
        queries[i].second = i;
    }

    sort(dolls.begin(), dolls.end());
    sort(queries.begin(), queries.end(), [] (pair<pi, int> a, pair<pi, int> b) {return a.first.second < b.first.second;});

    int reached = 0;
    dp[0] = INF;
    int cur_query = 0;
    for (int i = 0; i < N; i++) {
        while (cur_query < Q && queries[cur_query].first.second < dolls[i].height) {
            process_query(cur_query);
            cur_query++;
        }


        /* A pair of dolls (i, j) after sorting do NOT fit inside one another iff
         * i < j => diameter(i) >= diameter(j)
         */

        int pos = upper_bound(dp.begin(), dp.end(), dolls[i].diameter, gcomp) - dp.begin();
        dp[pos] = dolls[i].diameter;
        reached = max(reached, pos);
    }
    while (cur_query < Q) {
        process_query(cur_query);
        cur_query++;
    }

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}