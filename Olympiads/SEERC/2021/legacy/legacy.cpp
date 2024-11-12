#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N;
string s;

vector<int> positions[3];
vector<pi> ans;
vector<int> pref;

void fail(void)
{
    printf("NO\n");
    exit(0);
}

int main(void)
{
    cin >> N >> s;
    N = N * 2;

    pref.resize(N);
    ans.resize(N);
    ans.clear();

    int cnt[3] = {0, 0, 0};
    for (int i = 0; i < N; i++) {
        cnt[s[i] - 'A']++;

        positions[s[i] - 'A'].pb(i);
    }

    int sum = cnt[0] + cnt[1] + cnt[2];

    int v = sum / 2 - cnt[1];
    int a2 = sum / 2 - cnt[2];
    int c2 = sum / 2 - cnt[0];

    if (min(v, min(c2, a2)) < 0) {
        fail();
    }

    int p = 0;
    stack<int> aq;
    for (int i = cnt[1] - a2; i < cnt[1]; i++) {
        while (p < positions[1][i]) {
            if (s[p] == 'A') {
                aq.push(p);
            }
            p++;
        }

        if (aq.empty()) {
            fail();
        }

        ans.pb(mp(aq.top(), positions[1][i]));

        s[aq.top()] = 'B';
        aq.pop();
    }

    int r = N - 1;
    stack<int> cq;
    for (int i = c2 - 1; i >= 0; i--) {
        while (r > positions[1][i]) {
            if (s[r] == 'C') {
                cq.push(r);
            }
            r--;
        }

        if (cq.empty()) {
            fail();
        }

        ans.pb(mp(positions[1][i], cq.top()));

        s[cq.top()] = 'B';
        cq.pop();
    }

    stack<int> l;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'A') {
            l.push(i);
        }
        else if (s[i] == 'C') {
            if (l.empty()) {
                fail();
            }

            ans.pb(mp(l.top(), i));
            l.pop();
        }
    }

    printf("YES\n");
    for (int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }

    return 0;
}