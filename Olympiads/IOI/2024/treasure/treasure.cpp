#include "treasure.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int MAXNUM = 5e8;
const int MAXN = 4e4;
const int MAXV = 2e9;


const int SAVE_PER_NOTE = 24000;
const int IS_X = MAXNUM * 2 + 2;

bool cmp_parts(int x)
{
    int x1 = x / SAVE_PER_NOTE;
    int x2 = x % SAVE_PER_NOTE;

    return x1 < x2;
}

bool encodingsort(const pi& a, const pi& b)
{
    if (a.second == b.second) {
        if (cmp_parts(a.first)) {
            return false;
        }
        else if (cmp_parts(b.first)) {
            return true;
        }
        else {
            return false;
        }
    }

    return a.second < b.second;
}

vector<int> encode(vector<pair<int, int>> P) {
    int N = P.size();

    // Attention to sorting: encoding sort must fulfill the prerequisites of a comparator function
    sort(P.begin(), P.end(), encodingsort);

    vector<int> res;

    for (int i = 0; i < N; i++) {
        int x, y;
        tie(x, y) = P[i];

        int x1 = x / SAVE_PER_NOTE;
        int x2 = x % SAVE_PER_NOTE;

        // Make 3 notes for this pair
        int n1 = 0;
        int n2 = 0; 
        int n3 = 0;

        // NOTE 1: x1 + position of y
        n1 = IS_X + x1 * MAXN + i;

        // NOTE 2: x2 + position of y
        n2 = IS_X + x2 * MAXN + i;

        // NOTE 3: y + is x1 < x2
        n3 = y * 2 + cmp_parts(x);

        res.pb(n1);
        res.pb(n2);
        res.pb(n3);
    }

    return res;
}

void order(int& s, int& l)
{
    if (s > l) {
        swap(s, l);
    }
}

vector<pair<int, int>> decode(vector<int> S) {
    int N = S.size() / 3;

    sort(S.begin(), S.end());

    vector<pi> ans(N, mp(0, 0));
    vector<int> y(N, 0);
    vector<bool> cmp(N, false);
    vector<int> x(N, -1);

    for (int i = 0; i < S.size(); i++) {
        if (S[i] >= IS_X) {
            // This is a type n2 or n1
            S[i] -= IS_X;

            int cur = S[i] / MAXN;
            int pos = S[i] % MAXN;

            if (x[pos] == -1) {
                x[pos] = cur;
            }
            else {
                int x1 = x[pos];
                int x2 = cur;

                if (cmp[pos]) {
                    order(x1, x2);
                }
                else {
                    order(x2, x1);
                }

                x[pos] = x1 * SAVE_PER_NOTE + x2;
            }
        }
        else {

            // This is a type n3
            y[i] = S[i] / 2;
            cmp[i] = S[i] % 2;
            x[i] = -1;
        }
    }

    for (int i = 0; i < N; i++) {
        ans[i] = mp(x[i], y[i]);
    }

    return ans;
}
