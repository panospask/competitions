#include <bits/stdc++.h>
#define sq(var) ((var) * (var))

using namespace std;

typedef long long ll;

struct Carrot {
    int len;
    int pieces;

    Carrot (int l) {
        len = l;
        pieces = 1;
    }

    // Internal use only
    ll time_taken(int p) {
        if (p > len) {
            return len;
        }

        ll piecelength = len / p;

        // Somee pieces will be one longer than others
        int bigpieces = len % p;
        int smallpieces = p - bigpieces;

        return sq(piecelength) * smallpieces + sq(piecelength + 1) * bigpieces;
    }

    // time saved if we add one more cut to the current carrot
    ll saved(void) {
        return time_taken(pieces) - time_taken(pieces + 1);
    }
    void add_cut(void) {
        pieces++;
    }
    ll res(void) {
        return time_taken(pieces);
    }
};

bool operator < (Carrot a, Carrot b)
{
    return a.saved() < b.saved();
}

int N, K;
priority_queue<Carrot> q;

int main(void)
{
    scanf("%d %d", &N, &K);

    for (int i = 0; i < N; i++) {
        int l;
        scanf("%d", &l);

        q.push(Carrot(l));
    }

    while (N < K) {
        Carrot cur = q.top();
        q.pop();

        cur.add_cut();
        N++;

        q.push(cur);
    }

    ll ans = 0;
    while (!q.empty()) {
        Carrot cur = q.top();
        q.pop();

        ans += cur.res();
    }

    printf("%lld\n", ans);

    return 0;
}