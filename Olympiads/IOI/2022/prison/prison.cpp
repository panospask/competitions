#include "prison.h"

using namespace std;

int M;
vector<int> pow2;
vector<vector<int>> s;

vector<vector<int>> devise_strategy(int N)
{
    pow2.push_back(1);
    while (pow2.back() < N)
        pow2.push_back(pow2.back() * 2);
    M = pow2.back();
    int K = 2 * (pow2.size() - 1);

    s.resize(K + 1, vector<int>(N + 1));

    for (int state = 0; state <= K; state++) {
        int P = (state + 1) / 2;
        // Everything up until N / pow2[P] has been the same for all

        // Check wether the other bag has more or less
        // Even number = less, odd number = more
        bool more = state % 2;

        // Bag A is 0, Bag B is 1
        if (state % 4 == 0 || (state + 1) % 4 == 0)
            s[state][0] = 0;
        else
            s[state][0] = 1;
        int curbag = s[state][0];

        for (int v = 1; v <= N; v++) {
            int res = v - 1;
            for (int p = 0; p < P; p++)
                res %= M / pow2[p];

            bool cur_more = res >= M / pow2[P];

            if (!(more ^ cur_more)) {
                // Advance state
                // Must have room for improvement :)
                res %= M / pow2[P];
                if (P == pow2.size() - 1) {
                    // Impossible
                    s[state][v] = 0;
                }
                else {
                    int nxt = 2 * P + 1;
                    if (res < M / pow2[P + 1])
                        nxt++;

                    s[state][v] = nxt;
                }
            }
            else if (more) {
                s[state][v] = (curbag + 1) * -1;
            }
            else {
                s[state][v] = (!curbag + 1) * -1;
            }
        }
    }

    return s;
}