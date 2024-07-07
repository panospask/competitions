#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1001;

// Try two stacks method

struct ImprovedStack {
    stack<int> s;
    stack<bitset<MAXV>> possible;

    ImprovedStack(void) {
        bitset<MAXV> init;
        init.set(0, 1);
        possible.push(init);
    }

    void push(int a) {
        bitset<MAXV> cur = possible.top() << a;

        possible.push(cur | possible.top());
        s.push(a);
    }
    int top(void) {
        return s.top();
    }
    bitset<MAXV> pos(void) {
        return possible.top();
    }
    void pop(void) {
        s.pop();
        possible.pop();
    }
    bool empty(void) {
        return s.empty();
    }
};

int N, S;
vector<int> a;
ImprovedStack s1, s2;

void add(int x)
{
    s2.push(x);
}
void remove(int x)
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
bool good(void)
{
    auto p1 = s1.pos();
    auto p2 = s2.pos();

    p1._Find_next(0);

    for (int v = 0; v <= S; v = p1._Find_next(v)) {
        if (p2.test(S - v)) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    scanf("%d %d", &N, &S);

    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int ans = N + 1;
    int r = 0;

    for (int l = 0; l < N; l++) {
        while (r < N && !good()) {
            add(a[r]);
            r++;
        }

        if (good()) {
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