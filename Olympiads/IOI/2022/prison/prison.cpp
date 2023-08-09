#include "prison.h"

using namespace std;

int M;
vector<int> pow3;
vector<vector<int>> s;

vector<vector<int>> devise_strategy(int N)
{
    pow3.push_back(1);
    while (pow3.back() < N)
        pow3.push_back(pow3.back() * 3);
    M = pow3.back();
    int K = 3 * (pow3.size() - 1) - 2;

    s.resize(K + 1, vector<int>(N + 1));

    for (int state = 0; state <= K; state++) {
        int P = (state + 2) / 3;
        // Everything up until N / pow3[P] has been the same for all

        // Check wether the other bag has more or less
        // More than (or equal to) 0/3, 1/3, and 2/3 respectively
        int more = state % 3;

        // Bag A is 0, Bag B is 1
        if (state % 6 == 0 || (state + 1) % 6 == 0 || (state + 2) % 6 == 0)
            s[state][0] = 0;
        else
            s[state][0] = 1;
        int curbag = s[state][0];

        for (int v = 1; v <= N; v++) {
            int res = v - 1;
            for (int p = 0; p < P; p++)
                res %= M / pow3[p];

            int cur_more = res / (M / pow3[P]);

            if (M / pow3[P] == 1) {
                if (cur_more == 0) {
                    s[state][v] = (curbag + 1) * -1;
                }
                else {
                    s[state][v] = (!curbag + 1) * -1;
                }
            }
            else if (more == cur_more) {
                // Advance state
                // Must have room for improvement :)
                res %= M / pow3[P];

                int div = (M / pow3[P + 1]);
                int nxt = 3 * P + 1;
                int r = res / div;

                if (div == 1) {
                    if (r == 0) {
                        s[state][v] = (curbag + 1) * -1;
                    }
                    else if (r == 1) {
                        s[state][v] = nxt;
                    }
                    else {
                        s[state][v] = (!curbag + 1) * -1;
                    }
                }
                else {
                    s[state][v] = nxt + (r + 2) % 3;
                    ;
                }
            }
            else if (more > cur_more) {
                s[state][v] = (curbag + 1) * -1;
            }
            else {
                s[state][v] = (!curbag + 1) * -1;
            }
        }
    }

    return s;
}