#include <bits/stdc++.h>

using namespace std;

void solve(void)
{
    vector<int> a_cont;
    vector<int> b_cont;

    int n;
    scanf("%d", &n);
    a_cont.assign(2 * n, 0);
    b_cont.assign(2 * n, 0);

    int cur = -1;
    int cont = 0;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        if (num == cur)
            cont++;
        else {
            cont = 1;
            cur = num;
        }

        a_cont[cur] = max(a_cont[cur], cont);
    }

    cur = -1;
    cont = 0;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        if (num == cur)
            cont++;
        else {
            cont = 1;
            cur = num;
        }

        b_cont[cur] = max(b_cont[cur], cont);
    }

    int ans = 0;
    for (int i = 0; i < 2 * n; i++)
        ans = max(ans, a_cont[i] + b_cont[i]);

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}