#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, K, Q;
vector<tuple<int,int,int>> events;
vector<int> ans;

int main(void) {
    scanf("%d %d %d", &N, &K, &Q);

    ans.assign(Q, 0);
    for (int i = 0; i < Q; i++) {
        int p, l, r;
        scanf("%d %d %d", &p, &l, &r);
        events.push_back({l, -1, i});
        events.push_back({r, 1, i});
    }

    int present = N;
    sort(events.begin(), events.end());
    for (auto [t, v, i] : events) {
        if (v == -1) {
            present--;
        }
        else {
            if (present == 0) {
                ans[i] = 1;
            }
            present++;
        }
    }

    int keys = K;
    bool possible = true;
    for (auto [t, v, i] : events) {
        if (v == -1) {
            if (ans[i]) {
                keys--;
                possible = possible && keys >= 0;
            }
        }
        else {
            if (ans[i]) {
                keys++;
            }
        }
    }

    if (!possible) {
        printf("impossible\n");
        return 0;
    }
    for (int i = 0; i < Q; i++) {
        printf("%d", ans[i]);
    }
    printf("\n");
}