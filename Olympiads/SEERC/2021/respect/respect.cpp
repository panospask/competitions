#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int N, X, R, P, K;

// The positions in which boss places regeneration stack
vector<int> regen_pos;
vector<bool> regenerates;

// The positions in which we place poison stack
vector<int> poison;

int main(void)
{
    scanf("%d %d %d %d %d", &N, &X, &R, &P, &K);

    // Insert poison at the first K positions

    ll ans = (ll)N * X;

    regenerates.assign(N, false);

    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '1') {
            regenerates[i] = true;
            if (i >= K) {
                regen_pos.pb(i);

                ans -= (ll)R * (N - i);
            }
        }
        else {
            regenerates[i] = false;
        }
    }

    for (int i = 0; i < K; i++) {
        if (regenerates[i] == false) {
            poison.pb(i);
        }
        ans += (ll)P * (N - i);
    }

    // Swap as many of the poison placement on top of regeneration placements to cancel them out
    int p = poison.size() - 1;
    int r = 0;

    while (p >= 0 && r < regen_pos.size()) {
        // Check if poison[p] can be moved to regen_pos[r]

        ll gain = (ll)R * (N - regen_pos[r]);
        ll loss = (ll)P * (regen_pos[r] - poison[p]);
        if (gain - loss >= 0) {
            ans += gain - loss;
            r++;
            p--;
        }
        else {
            break;
        }
    }

    printf("%lld\n", ans);

    return 0;
}