#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

// dp[i][j]: Who wins if the card at the table is the j-th card of player i
vector<vector<int>> dp;

vector<vector<pi>> best;
vector<vector<pi>> cards;

// Does player i win?
int calculate_dp(int i, int j)
{
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = 2;

    // From the cards with highest attack than opponents defence, pick the one with best defence
    int pos = lower_bound(cards[!i].begin(), cards[!i].end(), mp(cards[i][j].second + 1, 0)) - cards[!i].begin();

    if (pos == cards[!i].size())
        return dp[i][j] = i;

    int opt = best[!i][pos].second;
    return dp[i][j] = calculate_dp(!i, opt);
}

void read_cards(int k)
{
    int N;
    scanf("%d", &N);
    best[k].resize(N);
    cards[k].resize(N);
    dp[k].assign(N, -1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &cards[k][i].first);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &cards[k][i].second);
    }

    sort(cards[k].begin(), cards[k].end());
    best[k][N - 1] = mp(cards[k][N - 1].second, N - 1);

    for (int i = N - 2; i >= 0; i--) {
        best[k][i] = max(best[k][i + 1], mp(cards[k][i].second, i));
    }
}

void solve(void)
{
    best.resize(2);
    cards.resize(2);
    dp.resize(2);

    read_cards(0);
    read_cards(1);

    int w = 0, d = 0, l = 0;
    for (int i = 0; i < cards[0].size(); i++) {
        int r = calculate_dp(0, i);
        if (r == 0)
            w++;
        else if (r == 2)
            d++;
        else
            l++;
    }

    printf("%d %d %d\n", w, d, l);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}