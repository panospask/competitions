#include <vector>
#include <stack>
#include "allenamento.h"

using namespace std;

typedef long long ll;

stack<int> s;
long long conta(int N, vector<int> A) {

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        while (!s.empty() && A[s.top()] < A[i])
            s.pop();

        if (!s.empty())
            ans += i - s.top();
        s.push(i);
    }

    return ans;
}
