#include "cave.h"
#include <bits/stdc++.h>

const int MAXN = 5000;

using namespace std;

int n;
int D[MAXN];
int S[MAXN];
int is_up[MAXN];
int proper_switch[MAXN];

bool test_door(int S[], int door)
{
    int a = tryCombination(S);

    if (a == -1 || a > door)
        return true;
    else
        return false;
}

void set_everything(int from, int to, bool spec)
{
    for (int i = 0; i < n; i++) {
        if (D[i] != -1)
            continue;

        if (i >= from && i < to)
            S[i] = spec;
        else
            S[i] = !spec;
    }
}

void exploreCave(int N)
{
    n = N;

    for (int i = 0; i < n; i++)
        D[i] = -1;

    for (int door = 0; door < n; door++) {
        // Find the best for each door

        // Begin by trying every possible switch closed
        for (int i = 0; i < n; i++)
            if (D[i] == -1)
                S[i] = false;

        if (test_door(S, door))
            is_up[door] = false;
        else
            is_up[door] = true;

        // Switch is contained in [l...r)
        int l = 0;
        int r = n;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            set_everything(l, mid, is_up[door]);

            if (test_door(S, door))
                r = mid;
            else
                l = mid;
        }

        D[l] = door;
        S[l] = is_up[door];
    }

    answer(S, D);
}
