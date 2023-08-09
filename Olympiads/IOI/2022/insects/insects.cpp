#include <bits/stdc++.h>
#include "insects.h"
#define pb push_back

using namespace std;

int N, D;
vector<bool> marked;
set<int> latest_iter;
int cnt = 0;

void clear_latest(void)
{
    for (int i = 0; i < N; i++) {
        // Can survive with only the ones in latest_iteration(they more more than the minimum)
        if (latest_iter.find(i) == latest_iter.end()) {
            marked[i] = true;
        }
        else {
            move_outside(i);
            cnt--;
            marked[i] = false;
        }
    }
    latest_iter.clear();
}

bool is_atleast(int x)
{
    for (int i = 0; i < N; i++) {
        if (marked[i])
            continue;

        move_inside(i);
        if (press_button() > x) {
            move_outside(i);
        }
        else {
            marked[i] = true;
            latest_iter.insert(i);
            cnt++;
        }

        if (cnt == x * D)
            return true;
    }

    return false;
}

int min_cardinality(int n)
{
    N = n;
    marked.assign(N, false);

    for (int i = 0; i < N; i++) {
        move_inside(i);
        if (press_button() == 1) {
            D++;
            marked[i] = true;
        }
        else {
            move_outside(i);
        }
    }

    cnt = D;
    int l = 1;
    int r = N / D;

    while (r > l) {
        int mid = (l + r + 1 + ((r - l) > 10)) / 2;
        if (is_atleast(mid)) {
            l = mid;
            latest_iter.clear();
        }
        else {
            r = mid - 1;
            clear_latest();
        }
    }

    return l;
}