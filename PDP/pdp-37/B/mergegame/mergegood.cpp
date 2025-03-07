#include <bits/stdc++.h>

using namespace std;

int N;
stack<int> s;

void process(int v)
{
    while (!s.empty() && s.top() < v) {
        s.pop();
    }

    if (!s.empty() && s.top() == v) {
        s.pop();
        process(v + 1);
    }
    else {
        s.push(v);
    }
}

int main(void)
{
    freopen("mergegame.in", "r", stdin);
    freopen("mergegame.out", "w", stdout);

    int type;
    scanf("%d", &type);

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int e;
        scanf("%d", &e);
        process(e);
    }

    int ans = 0;
    while (!s.empty()) {
        ans = max(ans, s.top());
        s.pop();
    }
    printf("%d\n", ans);
}