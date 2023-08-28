#include <vector>
#define pb push_back
#include "messy.h"

using namespace std;

int N;

// Insert elements in [l..r)
void insert_elements(int l, int r)
{
    if (l == r - 1) {
        return;
    }

    string x;

    x.resize(N);
    for (int i = 0; i < l; i++)
        x[i] = '0';
    for (int i = r; i < N; i++)
        x[i] = '0';
    for (int i = l; i < r; i++)
        x[i] = '1';

    int mid = (l + r) / 2;
    for (int i = l; i < mid; i++) {
        x[i] = '0';
        add_element(x);
        x[i] = '1';
    }

    insert_elements(l, mid);
    insert_elements(mid, r);
}

vector<int> p;

// Half of the possible positions will be in the first half
void find_half(int l, int r, vector<int> possible)
{
    if (l == r - 1) {
        p[possible.front()] = l;
        return;
    }

    string x;
    x.resize(N);
    for (int i = 0; i < N; i++)
        x[i] = '0';

    for (auto i : possible) {
        x[i] = '1';
    }
    vector<int> p1, p2;
    for (auto i : possible) {
        x[i] = '0';
        if (check_element(x))
            p1.push_back(i);
        else
            p2.push_back(i);

        x[i] = '1';
    }

    int mid = (l + r) / 2;
    find_half(l, mid, p1);
    find_half(mid, r, p2);
}

vector<int> restore_permutation(int n, int w, int r)
{
    N = n;
    p.resize(N);

    insert_elements(0, N);
    compile_set();

    vector<int> init;
    for (int i = 0; i < N; i++)
        init.pb(i);
    find_half(0, N, init);

    return p;
}
