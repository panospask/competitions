#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<char> a;
deque<int> bears;
deque<int> goodbears;

void solve(void) {
    scanf("%d", &N);

    int cur = 0;
    a.resize(N);

    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);
        a[i] = c;

        int type = (c == 'B');
        if (type != cur || bears.empty()) {
            cur = type;
            bears.push_back(0);
        }
        bears.back()++;
    }

    if (a[0] == 'B') {
        bears.pop_front();
    }
    if (a[N - 1] == 'P') {
        bears.pop_back();
    }

    // Create even better bears
    ll ans = 0;
    while (bears.size() >= 2) {
        if (bears[0] * bears[1] % 2 == 0) {
            ans += bears[0] * bears[1] / 2;

            if (goodbears.size()) {
                goodbears.back() += bears[1];
            }
            else {
                ;
            }

            if (bears.size() >= 3) {
                bears[2] += bears[0];
            }
            else {
                ;
            }
        }
        else {
            goodbears.push_back(bears[0]);
            goodbears.push_back(bears[1]);
        }

        bears.pop_front();
        bears.pop_front();
    }
    if (!bears.empty()) {
        exit(EXIT_FAILURE);
    }
    swap(bears, goodbears);

    while (bears.size() >= 2) {
        int s = bears.size();
        if ((ll)bears[0] * bears[1] % 2 == 0) {
            ans += (ll)bears[0] * bears[1] / 2;
            int v = bears[0];
            bears.pop_front();
            bears.pop_front();
            if (bears.size()) {
                bears[0] += v;
            }
        }
        else {
            if ((ll)bears[s - 1] * bears[s - 2] % 2 == 0) {
                ans += (ll) bears[s - 1] * bears[s - 2] / 2;
            }
            else {
                ans += ((ll)bears[s - 1] * bears[s - 2] - 1) / 2 + 1;
            }
            int v = bears[s - 1];
            bears.pop_back();
            bears.pop_back();

            if (bears.size()) {
                bears.back() += v;
            }
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d",&t);

    while (t--) {
        solve();
    }

    return 0;
}