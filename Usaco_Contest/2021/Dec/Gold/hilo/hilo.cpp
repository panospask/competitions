#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int n;
vector<int> p;
vector<int> pos;
vector<bool> isfinishing;
vector<int> prv_lo;
vector<int> prv_hi;
stack<int> s;

int main(void)
{
    // freopen("hilo.in", "r", stdin);
    // freopen("hilo.out", "w", stdout);

    scanf("%d", &n);
    p.resize(n + 1);
    pos.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        pos[p[i]] = i;
    }

    prv_hi.resize(n + 1);
    prv_lo.resize(n + 1);
    isfinishing.resize(n + 1);

    s.push(0);

    for (int i = n; i > 0; i--) {
        while (s.top() > pos[i])
            s.pop();

        prv_hi[pos[i]] = s.top();
        s.push(pos[i]);
    }
    while (s.size() != 1)
        s.pop();

    int cnt = 0;
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        while (s.top() > pos[i]) {
            cnt -= isfinishing[s.top()];
            s.pop();
        }

        isfinishing[pos[i]] = (prv_hi[pos[i]] != 0 && (s.size() == 1 || prv_hi[s.top()] != prv_hi[pos[i]]));
        cnt += isfinishing[pos[i]];
        s.push(pos[i]);

        cout << cnt << endl;
    }

    return 0;
}