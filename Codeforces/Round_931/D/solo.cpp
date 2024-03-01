#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1ll << (pos)))

using namespace std;

typedef long long ll;

const int MAXB = 64;

vector<ll> pow2;
vector<ll> s;
vector<ll> full_up_to;

void prnt_ans(void)
{
    printf("%d\n", (int)s.size() - 1);
    for (auto f : s) {
        printf("%lld ", f);
    }
    printf("\n");
}

void solve(void)
{
    ll N, M;
    scanf("%lld %lld", &N, &M);

    s.clear();
    s.push_back(N);

    bool started = false;
    bool sac_2 = false;
    bool sac_1 = false;
    for (int i = MAXB - 1; i >= 0; i--) {
        if (!started && CHECK_BIT(N, i)) {
            if (CHECK_BIT(M, i)) {
                // Sacrifice second 1
                sac_2 = true;
            }
            else {
                // Crucial point
                sac_1 = true;
            }
                started = true;
        }
        else if (CHECK_BIT(N, i)) {
            if (!CHECK_BIT(M, i) && sac_2) {
                s.push_back((N ^ (1ll << i)) | full_up_to[i]);
                if (s.back() != M)
                    s.push_back(M);
                prnt_ans();
                return;
            }
            else if (sac_1) {
                s.push_back(full_up_to[i + 1]);
                if (s.back() != M)
                    s.push_back(M);
                prnt_ans();
                return;
            }
        }
        else if (CHECK_BIT(M, i)) {
            printf("-1\n");
            return;
        }
    }

    printf("Error\n");
    return;
}

void calculate(void)
{
    full_up_to.resize(MAXB);
    full_up_to[0] = 0;

    for (int i = 0; i < MAXB - 1; i++) {
        full_up_to[i + 1] = full_up_to[i] ^ (1ll << i);
    }
}

int main(void)
{
    calculate();

    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}