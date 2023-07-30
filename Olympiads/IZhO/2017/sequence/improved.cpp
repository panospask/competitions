#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

const int MAXD = 20;
const int B = MAXD / 2;
const int CHANGE = (1 << B);

typedef pair<int, int> pi;

int N;

vector<int> a;
vector<int> k;
vector<int> prv;

// dp[l][r][k]: The best one from numbers all number v that fulfill:
// l[v] = l
// bitcount(r[v] & r) = k
pi dp[1 << B][1 << B][B + 1];
int l[1 << MAXD];
int r[1 << MAXD];

void calculate_l_r(void)
{
    for (int i = 0; i < (1 << MAXD); i++) {
        l[i] = i / CHANGE;
        r[i] = i % CHANGE;
    }
}

int main(void)
{
    scanf("%d", &N);

    calculate_l_r();

    a.resize(N + 1);
    prv.resize(N + 1);
    k.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &k[i]);
    }

    pi opt;
    for (int i = 1; i <= N; i++) {
        pi best = mp(0, 0);
        int v = a[i];

        for (int lx = 0; lx < 1 << B; lx++) {
            int bits = __builtin_popcount(lx & l[v]);
            int rem = k[i] - bits;

            if (rem >= 0 && rem <= B)
                best = max(best, dp[lx][r[v]][rem]);
        }

        prv[i] = best.s;
        int res = best.f + 1;

        for (int rx = 0; rx < 1 << B; rx++) {
            int bits = __builtin_popcount(rx & r[v]);
            dp[l[v]][rx][bits] = max(dp[l[v]][rx][bits], mp(res, i));
        }

        opt = max(opt, mp(res, i));
    }

    vector<int> ans;
    for (int i = opt.s; i != 0; i = prv[i])
        ans.push_back(i);
    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}