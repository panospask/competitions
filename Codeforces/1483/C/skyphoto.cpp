#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e18;

struct State {
    int minheight;
    int minbeauty;
    ll maxv;

    ll res(void) {
        return maxv + minbeauty;
    }

    void merge(State b) {
        maxv = max(maxv, b.maxv);
    }
};


struct ImprovedStack {
    stack<State> s;
    stack<ll> m;

    ImprovedStack(void) {
        m.push(-INF);
    }

    void push(State x) {
        s.push(x);
        m.push(max(m.top(), x.res()));
    }
    void pop(void) {
        s.pop();
        m.pop();
    }
    State top(void) {
        return s.top();
    }
    ll opt(void) {
        return m.top();
    }
    bool empty(void) {
        return s.empty();
    }
};

int N;
vector<int> h;
vector<int> b;
ImprovedStack s;

/// dp[i]: Maximum beauty if photos are taken for up to and including i
vector<ll> dp;

int main(void)
{
    scanf("%d", &N);

    h.resize(N);
    b.resize(N);
    dp.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < N; i++) {
        ll prv = i ? dp[i - 1] : 0;
        State cur = {h[i], b[i], prv};

        while (!s.empty() && s.top().minheight > cur.minheight) {
            cur.merge(s.top());
            s.pop();
        }
        
        s.push(cur);
        dp[i] = s.opt();
    }

    printf("%lld\n", dp[N - 1]);

    return 0;
}