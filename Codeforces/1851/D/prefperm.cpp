#include <bits/stdc++.h>

using namespace std;

int N;
vector<bool> marked;
vector<int> perm;
void solve(void)
{
    scanf("%d", &N);

    marked.assign(N + 1, false);
    perm.resize(N);

    long long prv = 0;
    bool getskip = true;
    int skipval = 0;
    for (int i = 0; i < N - 1; i++) {
        long long num;
        scanf("%lld", &num);

        long long v = num - prv;
        if (v > N ||  marked[v]) {
            if (!getskip || v > 2 * N) {
                for (int j = i + 1; j < N - 1; j++) {
                    long long  tmp;
                    scanf("%lld", &tmp);
                }
                printf("NO\n");
                return;
            }
            else {
                skipval = v;
                getskip = false;
            }
        }
        else {
            marked[v] = true;
        }
        prv = num;
    }

    if (getskip) {
        printf("YES\n");
        return;
    }

    int v1 = 0, v2 = 0;
    for (int i = 1; i <= N; i++) {
        if (!marked[i]) {
            if (v1)
                v2 = i;
            else
                v1 = i;
        }
    }

    if (v1 + v2 == skipval)
        printf("YES\n");
    else
        printf("NO\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}