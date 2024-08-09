#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

// prv[i]: Maximum j such that j < i and a[j] < a[i]
vector<int> prv;

// nxt[i]: Minimum j such that j > i and a[j] < a[i]
vector<int> nxt;

vector<int> ans;

void calculate(vector<int>& v)
{
    v.resize(N + 1);

    stack<int> s;
    s.push(0);

    for (int i = 1; i <= N; i++) {
        while (a[s.top()] >= a[i]) {
            s.pop();
        }

        v[i] = s.top();
        s.push(i);
    }
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    a[0] = 0;

    calculate(prv);

    reverse(a.begin() + 1, a.end());
    calculate(nxt);
    reverse(nxt.begin() + 1, nxt.end());
    reverse(a.begin() + 1, a.end());

    ans.assign(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        nxt[i] = N - nxt[i];
    }

    for (int i = 1; i <= N; i++) {
        int len = nxt[i] - prv[i];

        ans[len] = max(ans[len], a[i]);
    }
    for (int l = N - 1; l >= 0; l--) {
        ans[l] = max(ans[l], ans[l + 1]);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}