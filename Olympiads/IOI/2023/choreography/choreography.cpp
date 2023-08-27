#include "choreography.h"
#include <vector>
#define pb push_back

using namespace std;

int N;

struct State {
    // odd positions and even positions
    vector<int> vals[2];
    int add = 0;
    int shift = 0;

    bool rev = false;
    // How much do the even values gain/ the odd values lose
    int mod = 0;

    void shift_by(int i) {
        shift = (shift + i + N) % N;
    }
    void add_x(int x) {
        add = (add + x + N) % N;

        if (x % 2) {
            // Odd becomes even and vice versa
            rev = !rev;
        }
    }

    void swap_indices(void) {
        swap(vals[0], vals[1]);
    }
    void swap_values(void) {
        // The current even ones get a boost, the current odd ones get a nerf
        // Also the even/odd are swapped
        if (rev)
            mod++;
        else
            mod--;

        rev = !rev;
    }
};

void swap(State& a, State& b)
{
    swap(a.add, b.add);
    swap(a.rev, b.rev);
    swap(a.shift, b.shift);
    swap(a.mod, b.mod);
    swap(a.vals, b.vals);
}

// dancer i occupies position d[i]
State d;

// position i is occupied by dancer p[i]
State p;

void init(int n, vector<int> P) {
    N = n;

    for (int i = 0; i < N; i++) {
        p.vals[i % 2].pb(P[i]);
    }

    d.vals[0].resize(N / 2);
    d.vals[1].resize(N / 2);
    for (int i = 0; i < N; i++) {
        int dancer = p.vals[i % 2][i / 2];

        d.vals[dancer % 2][dancer / 2] = i;
    }
}

void move_right(int K) {
    d.add_x(K);
    p.shift_by(-K);
}

void move_left(int K) {
    d.add_x(-K);
    p.shift_by(K);
}

void swap_places() {
    d.swap_values();
    p.swap_indices();
}

void move_around() {
    swap(p, d);
}

int get_position(int D){
    int pos = (d.shift + D + N) % N;

    int res = d.vals[pos % 2][pos / 2];
    if (res % 2 == 0)
        res += d.mod;
    else
        res -= d.mod;

    res += d.add;

    res = (res % N + N) % N;

    return res;
}
