#include <bits/stdc++.h>
#include "mushrooms.h"
#define pb push_back

using namespace std;

int N;

const int W = 0, B = 1;
const int CUTOFF = 141;

// Once you have enough white/black to pass the cuttof
int white = 0;
int black = 0;

int nxt = 0;

vector<int> spec[2];

// use: true if white, false if black
void next_batch(int u)
{
    int build = min((int)spec[u].size(), N - nxt);

    // Construct with u
    vector<int> c;
    for (int i = nxt; i < nxt + build; i++) {
        c.pb(spec[u][i - nxt]);
        c.pb(i);
    }

    nxt += build;

    int res = use_machine(c);

    int diff_colour = res / 2 + res % 2;
    int same_colour = build - diff_colour;

    white += same_colour * (u == W) + diff_colour * !(u == W);
    black += same_colour * (u == B) + diff_colour * !(u == B);
}

int count_mushrooms(int n)
{
    spec[0].clear();
    spec[1].clear();

    N = n;
    nxt = 1;

    spec[W].pb(0);
    while (spec[0].size() < 2 && spec[1].size() < 2) {
        // Do presses 1 by 1
        if (nxt == N) {
            return spec[W].size();
        }

        int res = use_machine({0, nxt});
        if (res == 0) {
            spec[W].pb(nxt);
        }
        else {
            spec[B].pb(nxt);
        }

        nxt++;
    }

    while (spec[W].size() < CUTOFF && spec[B].size() < CUTOFF) {
        // Do presses 2 by 2
        int u = 0;
        if (spec[W].size() >= 2) {
            u = W;
        }
        else {
            u = B;
        }

        if (nxt == N) {
            return spec[W].size();
        }
        if (nxt == N - 1) {
            int l = use_machine({0, N - 1}) == 0;
            return spec[W].size() + l;
        }

        int res = use_machine({spec[u][0], nxt, spec[u][1], nxt + 1});
        if (res / 2 == 0) {
            spec[u].pb(nxt);
        }
        else {
            spec[!u].pb(nxt);
        }
        if (res % 2 == 0) {
            spec[u].pb(nxt + 1);
        }
        else {
            spec[!u].pb(nxt + 1);
        }

        nxt += 2;
    }

    white = spec[W].size();
    black = spec[B].size();

    while (nxt != N) {
        if (spec[0].size() >= CUTOFF)
            next_batch(0);
        else
            next_batch(1);
    }

    return white;
}