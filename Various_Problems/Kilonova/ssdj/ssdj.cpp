#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAXN = 1000;

int N;
char grid[MAXN][MAXN];
int pos[MAXN + 1];

ll ans = 0;

// Last chance :)
// Implement manual stack
int s[MAXN];
int ptr;

/* Computes the number of valid rectangles with top left corner at row r
 * such that the largest character in the rectangle is x and located on the top left corner.
 * 
 * cnt is a boolean variable denoting weather to also count the rectangles that have x in the
 * bottom left corner.
 */
inline void calculate_row(char x, int r, bool cnt)
{
    pos[N] = r;
    s[0] = N;
    ptr = 0;

    int same = 0;

    for (int c = N - 1; c >= 0; c--) {
        pos[c] = max(pos[c], r + 1);

        while (pos[c] < N && grid[pos[c]][c] < x) {
            pos[c]++;
        }

        if (pos[c] != N) {
            while (pos[s[ptr]] >= pos[c]) {
                same -= grid[pos[s[ptr]]][s[ptr]] == x;
                ptr--;
            }

            ptr++;
            s[ptr] = c;
            same += grid[pos[c]][c] == x;
        }

        if (grid[r][c] >= x) {

            if (grid[r][c] == x) {
                ans += ptr;
                ans -= same * (!cnt);

                ans -= pos[c] != N && (grid[pos[c]][c] != x || cnt);
            }


            // Clear the whole stack
            ptr = 0;

            same = 0;
            pos[c] = r;
            s[ptr] = c;
        }
    }
}

inline void calculate(char x, bool cnt)
{
    memset(pos, 0, (N + 1) * sizeof(int));

    for (int r = 0; r < N; r++) {
        calculate_row(x, r, cnt);
    }
}

void invert(void)
{
    reverse(grid, grid + N);
    for (int i = 0; i < N; i++) {
        reverse(grid[i], grid[i] + N);
    }
}

void read_input(void)
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }
}

int main(void)
{
    freopen("ssdj.in", "r", stdin);
    freopen("ssdj.out", "w", stdout);

    read_input();

    for (char c = 'b'; c <= 'z'; c++) {
        calculate(c, false);
    }

    invert();

    for (char c = 'b'; c <= 'z'; c++) {
        calculate(c, true);
    }

    printf("%lld\n", ans);

    return 0;
}