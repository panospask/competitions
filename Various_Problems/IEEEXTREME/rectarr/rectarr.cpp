#include <bits/stdc++.h>

using namespace std;

const int INF = 1e6;

struct Range {
    int start;
    int v1;
    int v2;
};

typedef long long ll;
typedef pair<int, int> pi;

int N, X;
vector<int> A;
ll ans = 0;

int main(void)
{
    scanf("%d %d", &N, &X);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    stack<Range> s;
    for (int i = 0; i < N; i++) {
        Range cur = {i, A[i], INF};

        int prv = INF;
        while (!s.empty() && s.top().v1 > cur.v1) {
            auto v = s.top();
            s.pop();

            ans = max(ans, min(prv, v.v1 + X));
        }
    }
}