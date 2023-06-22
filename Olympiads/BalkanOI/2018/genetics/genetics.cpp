#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t lll;

const ll MOD = (1ll << 61) - 1;

int n, m, k;
ll weightsum;
vector<ll> weight;
vector<vector<ll>> position_weight;

vector<vector<int>> clones;

int main(void)
{
    scanf("%d %d %d", &n, &m, &k);

    weight.resize(n);
    position_weight.resize(m, vector<ll>(4));
    clones.resize(n, vector<int>(m));

    srand(2222);
    for (int i = 0; i < n; i++) {
        weight[i] = (ll)rand() + 1;
        weightsum += weight[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);

            if (c == 'A')
                clones[i][j] = 0;
            else if (c == 'G')
                clones[i][j] = 1;
            else if (c == 'T')
                clones[i][j] = 2;
            else
                clones[i][j] = 3;

            position_weight[j][clones[i][j]] += weight[i];
            position_weight[j][clones[i][j]] %= MOD;
        }
    }

    for (int i = 0; i < n; i++) {

        ll total_difference = 0;
        lll expect_diff = weightsum - weight[i];
        expect_diff = (expect_diff % MOD) * k;
        expect_diff = (expect_diff % MOD + MOD) % MOD;

        for (int pos = 0; pos < m; pos++) {
            for (int v = 0; v < 4; v++) {
                if (clones[i][pos] == v)
                    continue;

                total_difference += position_weight[pos][v];
                total_difference %= MOD;
            }
        }

        if (total_difference == expect_diff) {
            printf("%d\n", i + 1);
            break;
        }
    }

    return 0;
}