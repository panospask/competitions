#include <bits/stdc++.h>

using namespace std;

struct cow {
    int w, x, d;

    void read_cow(void) {
        scanf("%d %d %d", &w, &x, &d);
        if (d == -1)
            d = 0;
        d = !d;
    }
};

typedef struct cow Cow;

int N, L, W, T;

int pt[2], weightsum, meetings;
int add[2] = {L, 0};
int mul[2] = {-1, 1};


vector<Cow> cows;
vector<int> pos[2];

bool operator < (const Cow& a, const Cow& b)
{
    return a.x < b.x;
}

int calc_time(int d)
{
    if (pt[d] == pos[d].size() || pt[d] == -1)
        return INT_MAX;

    return add[d] + mul[d] * pos[d][pt[d]];
}

void add_cow(int d)
{
    T = calc_time(d);

    Cow c;
    if (!d) {
        c = cows[N - 1 - pt[d]];
    }
    else {
        c = cows[pt[d]];
    }

    pt[d]++;
    weightsum += c.w;
}

void calculate_meetings(Cow c)
{
    if (c.d == 0) {
        // Moves right
        int initial = upper_bound(pos[1].begin(), pos[1].end(), c.x) - pos[1].begin();
        int final = upper_bound(pos[1].begin(), pos[1].end(), c.x + 2 * T) - pos[1].begin();

        meetings += final - initial;
    }
    else {
        // Moves left
        int initial = lower_bound(pos[0].begin(), pos[0].end(), c.x) - pos[0].begin();
        int final = lower_bound(pos[0].begin(), pos[0].end(), c.x - 2 * T) - pos[0].begin();

        meetings += initial - final;
    }

    return;
}

int main(void)
{
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);

    scanf("%d %d", &N, &L);
    add[0] = L;
    cows.resize(N);

    W = 0;
    for (int i = 0; i < N; i++) {
        cows[i].read_cow();
        W += cows[i].w;
        pos[cows[i].d].push_back(cows[i].x);
    }
    W = ceil((double)W / 2);

    sort(cows.begin(), cows.end());

    sort(pos[1].begin(), pos[1].end());
    sort(pos[0].rbegin(), pos[0].rend());

    weightsum = 0;
    pt[0] = pt[1] = 0;

    while (weightsum < W) {
        T = INT_MAX;

        for (int d = 0; d <= 1; d++) {
            T = min(T, calc_time(d));
        }

        for (int d = 0; d <= 1; d++) {
            if (T == calc_time(d))
                add_cow(d);
        }
    }

    sort(pos[0].begin(), pos[0].end());

    meetings = 0;
    for (int i = 0; i < N; i++) {
        calculate_meetings(cows[i]);
    }
    meetings /= 2;

    printf("%d\n", meetings);

    return 0;
}