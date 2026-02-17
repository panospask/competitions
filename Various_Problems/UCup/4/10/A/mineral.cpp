#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int add(int i) {
    printf("+ %d\n", i + 1);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

int remove() {
    printf("-\n");
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

int N;
vector<int> rep;

void entangle(vector<int> q1, vector<int> q2) {
    if (q2.size() == 0) {
        return;
    }
    else if (q1.size() == 0) {
        return;
    }
    else if (q1.size() == 1 && q2.size() == 1) {
        add(q1[0]);
        int res = add(q2[0]);
        if (res == 1) {
            rep[q2[0]] = q1[0];
        }
        remove();
        remove();

        return;
    }

    int m1 = ceil((float)q1.size() / 2);

    for (int i = 0; i < m1; i++) {
        add(q1[i]);
    }

    int prv = m1;

    vector<int> v1, v2;
    for (int i = 0; i < q2.size(); i++) {
        int cur = add(q2[i]);

        if (cur == prv) {
            v1.pb(q2[i]);
        }
        else {
            v2.pb(q2[i]);
        }
        prv = cur;
    }

    for (int i = 0; i < m1 + q2.size(); i++) {
        remove();
    }

    entangle(vector<int>(q1.begin(), q1.begin() + m1), v1);
    entangle(vector<int>(q1.begin() + m1, q1.end()), v2);
}

// solve problem [l, r)
vector<int> solve(int l, int r) {
    if (l + 1 == r) {
        return vector<int>(1, l);
    }
    
    int mid = (l + r) / 2;

    vector<int> q1 = solve(l, mid);
    vector<int> q2 = solve(mid, r);

    entangle(q1, q2);

    vector<int> q;
    for (auto i : q1) {
        q.pb(i);
    }
    for (auto i : q2) {
        if (rep[i] == i) {
            q.pb(i);
        }
    }

    return q;
}

int main(void) {
    scanf("%d", &N);

    rep.resize(N);
    for (int i = 0; i < N; i++) {
        rep[i] = i;
    }

    solve(0, N);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (rep[i] == i) {
            ans++;
        }
    }

    vector<vector<int>> groups(N);

    for (int i = 0; i < N; i++) {
        int j = i;
        while (j != rep[j]) {
            j = rep[j];
        }
        groups[j].pb(i);
    }

    printf("! %d\n", ans);
    for (int i = 0; i < N; i++) {
        if (rep[i] == i) {
            printf("%d", (int)groups[i].size());
            for (auto j : groups[i]) {
                printf(" %d", j + 1);
            }
            printf("\n");
        }
    }
    fflush(stdout);
}