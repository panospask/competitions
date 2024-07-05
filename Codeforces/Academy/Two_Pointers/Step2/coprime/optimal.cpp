#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 5;

ll gcd(ll a, ll b)
{
    if (a < b) {
        swap(a, b);
    }
    if (a == INF) {
        return b;
    }

    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

// Stack that also returns the gcd of the elements in it
struct ImprovedStack {
    stack<ll> s, c;

    void init(void) {
        c.push(INF);
    }

    void push(ll x) {
        s.push(x);
        c.push(gcd(c.top(), x));
    }
    void pop(void) {
        s.pop();
        c.pop();
    }

    bool empty(void) {
        return s.empty();
    }

    ll top(void) {
        return s.top();
    }
    ll res(void) {
        return c.top();
    }
};

ImprovedStack s1, s2;

void add(ll x) 
{
    s2.push(x);
}

void remove(ll x)
{
    if (s1.empty()) {
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    assert(s1.top() == x);
    s1.pop();
}

ll res(void)
{
    return gcd(s1.res(), s2.res());
}

int N;
vector<ll> a;

int main(void)
{
    s1.init();
    s2.init();

    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    int ans = N + 1, r = 0;
    for (int l = 0; l < N; l++) {
        while (r < N && res() != 1) {
            add(a[r]);
            r++;
        }

        if (res() == 1) {
            ans = min(ans, r - l);
        }

        remove(a[l]);
    }

    if (ans == N + 1) {
        ans = -1;
    }

    printf("%d\n", ans);

    return 0;
}