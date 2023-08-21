#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, K;

typedef pair<int, int> pi;

vector<int> change_points;
vector<bool> top;
vector<bool> bottom;

void init(int k, vector<int> r)
{
    N = r.size();
    K = k;

    bottom.assign(N, false);
    top.assign(N, false);

    bool begun = true;
    for (int i = 0; i < N; i++) {
        int prv = (i - 1 + N) % N;

        if (r[prv] == 0 && r[i] == 1) {
            change_points.pb(i);
            bottom[i] = true;
        }
        else if (r[prv] == 1 && r[i] == 0) {
            change_points.pb(i);
            top[i] = true;
        }
    }
}

int find_bef(int x, vector<int>& v)
{
    return upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
}

int compare_plants(int x, int y)
{
    if (x == y)
        return 0;

    int prv = change_points[find_bef(x, change_points)];
    if (prv == x) {
        // x is an important point
        int mod = bottom[x] ? 1 : -1;

        if (x == change_points.front()) {
            if (y <= x || y >= change_points.back()) {
                return -1 * mod;
            }
        }
        else {
            int prv = change_points[find_bef(x, change_points) - 1];
            if (y >= prv && y <= x)
                return -1 * mod;
        }

        if (x == change_points.back()) {
            if (y <= change_points.front() || y >= x)
                return -1 * mod;
        }
        else {
            int nxt = change_points[find_bef(x, change_points) + 1];
            if (y >= x && y <= nxt)
                return -1 * mod;
        }

        return 0;
    }
    int nxt = change_points[(find_bef(x, change_points) + 1) % change_points.size()];

    if (nxt < prv) {
        nxt += N;
        y += N;
    }

    if (prv <= y <= nxt) {
        // Answer is either 1 or -1
        int mod = bottom[prv] ? 1 : -1;
        if (x<= y) {
            return -1 * mod;
        }
        else {
            return 1 * mod;
        }
    }
    else {
        return 0;
    }
}