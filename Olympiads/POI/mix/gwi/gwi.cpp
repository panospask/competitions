#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e15;

int N, S;
vector<int> l, r;
vector<int> opt;
vector<ll> pref;

ll ans = INF;
// The index at which we reverse course and then start following opt
int idx = -1;
// What we do before this index
bool first_left = false;

// The leftmost and rightmost free stars respectively
int leftstar = 0, rightstar = N - 1;

vector<int> path;

ll sum(int l, int r) 
{
    return pref[r + 1] - pref[l];
}

// Go left for k steps
void go_left(int k)
{
    int first = leftstar + k - 1;
    if (first >= S && leftstar <= S) {
        first++;
    }

    for (int i = first; i >= leftstar; i--) {
        if (i != S) {
            path.pb(i);
        }
    }

    leftstar = first + 1;
}

// Go right for k steps
void go_right(int k) 
{
    int first = rightstar - k + 1;
    if (first <= S && rightstar >= S) {
        first--;
    }

    for (int i = first; i <= rightstar; i++) {
        if (i != S) {
            path.pb(i);
        }
    }

    rightstar = first - 1;
}

int main(void)
{
    scanf("%d %d", &N, &S);
    S--;

    l.resize(N - 1);
    r.resize(N - 1);
    opt.resize(N - 1);
    pref.resize(N);

    pref[0] = 0;
    for (int i = 0; i < N - 1; i++) {
        scanf("%d %d", &l[i], &r[i]);
        opt[i] = min(l[i], r[i]);
        pref[i + 1] = pref[i] + opt[i];
    }

    ans = INF;
    idx = -1;
    first_left = false;
    leftstar = 0;
    rightstar = N - 1;

    if (S == 0) {
        ans = r[0] + sum(1, N - 2);
        first_left = true;
        idx = 0;
    }
    else if (S == N - 1) {
        ans = l[0] + sum(1, N - 2);
        first_left = false;
        idx = 0;
    }
    else {
        ll totprv = 0;
        for (int step = 1; step <= N - 1 - S; step++) {
            totprv += r[step - 1];
            if (totprv + l[step] + sum(step + 1, N - 2) < ans) {
                ans = totprv + l[step] + sum(step + 1, N - 2);
                idx = step;
                first_left = false;
            }
        }
        totprv = 0;
        for (int step = 1; step <= S; step++) {
            totprv += l[step - 1];
            if (totprv + r[step] + sum(step + 1, N - 2) < ans) {
                ans = totprv + r[step] + sum(step + 1, N - 2);
                idx = step;
                first_left = true;
            }
        }
    }
    
    printf("%lld\n", ans);

    // Recover the path
    path.pb(S);
    if (first_left) {
        go_left(idx);
        l[idx] = 1e9 + 1;
        opt[idx] = r[idx];
    }    
    else {
        go_right(idx);
        r[idx] = 1e9 + 1;
        opt[idx] = l[idx];
    }

    while (idx < N - 1) {
        int prv = idx - 1;
        bool cur_left = opt[idx] == l[idx];
        while (idx < N - 1 && (opt[idx] == l[idx]) == cur_left) {
            idx++;
        }
        idx--;

        int steps = idx - prv;

        if (cur_left) {
            go_left(steps);
        }
        else {
            go_right(steps);
        }

        idx++;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", path[i] + 1);
    }
    printf("\n");

    return 0;    
}