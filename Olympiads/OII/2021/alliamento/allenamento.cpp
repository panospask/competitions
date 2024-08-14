#include <bits/stdc++.h>
#include "allenamento.h"
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXN = 2e7;
stack<int> big;
stack<int> small;
vector<int> ans;
int active = 0;
stack<pi> vals;

void erase_values(int from, int to)
{
    int prv = to - 1;

    while (prv >= from) {
        int sz = prv - max(from, vals.top().first);

        active -= sz * vals.top().second;

        prv = vals.top().first;
        if (prv >= from) {
            vals.pop();
        }
        if (prv <= from) {
            break;
        }
    }
}

long long conta(int N, vector<int> A) 
{
    ans.assign(N + 1, 0);

    A.insert(A.begin(), 0);

    ll res = 0;

    big.push(0);
    small.push(0);
    vals.push(mp(0, 0));
    for (int i = 1; i <= N; i++) {
        while (big.top() > 0 && A[big.top()] < A[i]) {
            big.pop();
        }
        while (small.top() > 0 && A[small.top()] > A[i]) {
            small.pop();
        }

        if (small.top() > big.top()) {
            erase_values(big.top(), small.top());

            vals.push(mp(big.top(), 1));
            active += small.top() - big.top();
        }
        else {
            erase_values(small.top(), big.top());

            vals.push(mp(small.top(), 0));
        }

        res += active;

        big.push(i);
        small.push(i);
    }

    return res;
}
