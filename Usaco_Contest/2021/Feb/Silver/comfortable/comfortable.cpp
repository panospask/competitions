#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int EMPTY = 0;
const int PLACE = 1;
const int EXTRA = 2;

const int DIRS = 4;
const int d_x[DIRS] = {1, 0, -1, 0};
const int d_y[DIRS] = {0, 1, 0, -1};

int N;
map<pi, int> status;
int extra = 0;

void place_cow(int x, int y, bool isextra);

void check(int x, int y)
{
    int cnt = 0;
    pi empty = {-1, -1};
    for (int d = 0; d < DIRS; d++) {
        int n_x = x + d_x[d];
        int n_y = y + d_y[d];

        if (status[mp(n_x, n_y)]) {
            cnt++;
        }
        else {
            empty = mp(n_x, n_y);
        }
    }

    if (cnt == 3) {
        place_cow(empty.first, empty.second, true);
    }
}

void place_cow(int x, int y, bool isextra)
{
    status[mp(x, y)] = PLACE + isextra;
    if (isextra) {
        extra++;
    }

    check(x, y);
    for (int d = 0; d < DIRS; d++) {
        int n_x = x + d_x[d];
        int n_y = y + d_y[d];
        if (status[mp(n_x, n_y)]) {
            check(n_x, n_y);
        }
    }
}

int main(void)
{
    // freopen("comfortable.in", "r", stdin);
    // freopen("comfortable.out", "w", stdout);

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (status[mp(x, y)] == EXTRA) {
            extra--;
            status[mp(x, y)] = PLACE;
        }
        else {
            place_cow(x, y, false);
        }

        printf("%d\n", extra);
    }

    return 0;
}