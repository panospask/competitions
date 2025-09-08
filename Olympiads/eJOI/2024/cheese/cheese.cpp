#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int BITS = 18;


int add(ll a, ll b, int MOD) {
    ll c = a + b;
    if (c < 0) {
        c += MOD;
    }
    if (c >= MOD) {
        c -= MOD;
    }
    return c;
}

struct DSU {
    int size;
    int MOD;
    bool special = false;
    vector<int> rank;
    vector<int> rep;
    vector<ll> to_leader;

    void init(int N) {
        size = N;

        rank.assign(N, 0);
        rep.resize(N);
        to_leader.assign(N, 0);

        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
    }

    int find(int a) {
        while (rep[rep[a]] != rep[a]) {
            if (special) {
                to_leader[a] += to_leader[rep[a]];
            }
            else {
                to_leader[a] = add(to_leader[a], to_leader[rep[a]], MOD);
            }
            rep[a] = rep[rep[a]];
        }

        return rep[a];
    }

    // a = b + v
    // b = a - v
    bool unite(int a, int b, int v, bool make) {
        int l1 = find(a);
        int l2 = find(b);

        if (l1 == l2) {
            if (special) {
                return to_leader[a] - to_leader[b] == v;
            }
            else if (add(to_leader[a], -to_leader[b], MOD) == v) {
                return true;
            }
            return false;
        }

        if (!make) {
            return true;
        }

        if (rank[l1] < rank[l2]) {
            swap(l1, l2);
            swap(a, b);
            if (special) {
                v = -v;
            }
            else {
                v = add(0, -v, MOD);
            }
        }
        if (rank[l1] == rank[l2]) {
            rank[l1]++;
        }

        rep[l2] = l1;
        if (special) {
            to_leader[l2] = -v  + to_leader[a] - to_leader[b];
        }
        else {
            to_leader[l2] = add(add(-v, to_leader[a], MOD), -to_leader[b], MOD);
        }

        return true;
    }
};

int N, M;
DSU graph[BITS];
DSU special;

int main(void) {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < BITS; i++) {
        graph[i].MOD = (1 << i);
        graph[i].init(N);
    }
    special.special = true;
    special.init(N);

    while (M--) {
        int i, j, A, B;
        scanf("%d %d %d %d", &i, &j, &A, &B);
        i--; j--;

        bool s = B == -1;
        if (B == -1) {
            B = (1 << (BITS - 1));
        }

        int b = 0;
        bool ans = true;
        while ((1 << b) <= B && ans) {
            ans = graph[b].unite(i, j, A % (1 << b), false);
            b++;
        }
        if (s) {
            ans = ans && special.unite(i, j, A, false);
        }

        if (!ans) {
            printf("0\n");
            continue;
        }

        b = 0;
        while ((1 << b) <= B) {
            ans = graph[b].unite(i, j, A % (1 << b), true);
            b++;
        }
        if (s) { 
            special.unite(i, j, A, true);
        }

        printf("1\n");
    }

    return 0;
}