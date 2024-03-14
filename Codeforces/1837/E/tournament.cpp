#include <bits/stdc++.h>
#define MOD 998244353

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int k, n;
vector<int> cur_round;
vector<int> next_round;
vector<int> places_filled;
vector<ll> fact;

bool must_lose(int i, int lvl)
{
    int minimum_lose = (1<<(k-lvl-1));
    return i >= minimum_lose;
}

void impossible(void)
{
    printf("0\n");
    exit(EXIT_SUCCESS);
}

int main(void)
{
    scanf("%d", &k);
    n = 1 << k;

    fact.resize(n);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++)
        fact[i] = fact[i - 1] * i % MOD;

    cur_round.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cur_round[i]);
        if (cur_round[i] != -1)
            cur_round[i]--;
    }

    long long ans = 1;
    for (int r = 0; r < k; r++) {
        // The r-th round
        int lose_choice = 0;
        int advance;
        for (int i = 0; i < cur_round.size(); i += 2) {
            // Examine i and i + 1 as they will fight
            if (cur_round[i] != -1 && cur_round[i + 1] != -1) {
                bool first_lose = must_lose(cur_round[i], r);
                bool sec_lose = must_lose(cur_round[i + 1], r);

                if (first_lose == sec_lose)
                    impossible();

                if (!first_lose) {
                    swap(first_lose, sec_lose);
                    swap(cur_round[i], cur_round[i + 1]);
                }

                // Cannot pick loser, cannot pick order
                advance = cur_round[i + 1];
            }
            else {
                if (cur_round[i + 1] != -1)
                    swap(cur_round[i], cur_round[i + 1]);

                if (cur_round[i] != -1) {
                    // Determine if i wins or loses and act accordingly
                    if (must_lose(cur_round[i], r)) {
                        // Loser is decided, => Cannot change the pair order
                        // and cannot pick loser

                        advance = -1;
                    }
                    else {
                        // Winner is decided => Cannot change the pair order
                        // but can pick loser

                        lose_choice++;
                        advance = cur_round[i];
                    }
                }
                else {
                    lose_choice++;

                    // Free to choose the order of winner-loser
                    ans = ans * 2 % MOD;
                    advance = -1;
                }
            }

            next_round.push_back(advance);
        }

        ans = ans * fact[lose_choice] % MOD;
        swap(next_round, cur_round);
        next_round.clear();
    }

    printf("%lld\n", ans);

    return 0;
}