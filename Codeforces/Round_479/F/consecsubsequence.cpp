#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N;
map<int, pi> best;
vector<int> prv;

int main(void)
{
    scanf("%d", &N);

    pi opt = mp(0, 0);
    prv.resize(N);
    for (int i = 0; i < N; i++) {
        int v;
        scanf("%d", &v);

        pi res = mp(0, -1);
        if (best.find(v - 1) != best.end()) {
            res = best[v - 1];
        }

        prv[i] = res.second;
        best[v] = mp(res.first + 1, i);
        opt = max(opt, best[v]);
    }

    vector<int> ans;
    for (int i = opt.second; i != -1; i = prv[i])
        ans.push_back(i);
    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (auto i : ans)
        printf("%d ", i + 1);
    printf("\n");
    return 0;
}