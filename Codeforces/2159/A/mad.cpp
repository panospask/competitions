#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> ans;

int query(vector<int> v) {
    printf("? %d ", (int)v.size());
    for (auto i : v) {
        printf("%d ", i);
    }
    printf("\n");
    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

void solve(void) {
    scanf("%d", &N);
    
    ans.assign(2 * N + 1, 0);

    vector<int> pos;
    for (int i = 1; i <= 2 * N; i++) {
        pos.pb(i);
        int res = query(pos);
        
        if (res != 0) {
            pos.pop_back();
            ans[i] = res;
        }
    }

    pos.clear();
    for (int i = 2 * N; i > 0; i--) {
        while (i > 0 && ans[i] != 0) {
            pos.pb(i);
            i--;
        }

        if (i == 0) {
            break;
        }

        pos.pb(i);
        ans[i] = query(pos);
        pos.pop_back();
    }

    printf("! ");
    for (int i = 1; i <= 2 * N; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    fflush(stdout);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}