#include <vector>
#include <string>

using namespace std;

typedef long long ll;

int N;

string code = "ATC";

vector<vector<int>> pref[2];

vector<vector<vector<int>>> at;

void init(string a, string b)
{
    N = a.size();

    pref[0].resize(N, vector<int>(3));
    pref[1].resize(N, vector<int>(3));

    for (int i = 0; i < N; i++) {
        pref[0][i][code.find(a[i])]++;
        pref[1][i][code.find(b[i])]++;

        if (i != N - 1) {
            pref[0][i + 1] = pref[0][i];
            pref[1][i + 1] = pref[1][i];
        }
    }

    at.resize(N, vector<vector<int>>(3, vector<int>(3)));
    for (int i = 0; i < N; i++) {
        if (i)
            at[i] = at[i - 1];

        int c1 = code.find(a[i]);
        int c2 = code.find(b[i]);

        at[i][c1][c2]++;
    }
}

int get_cnt(int x, int y, int v, int from)
{
    int res = pref[from][y][v];
    if (x)
        res -= pref[from][x - 1][v];

    return res;
}

int get_swaps(int x, int y, int a, int b)
{
    int res = at[y][a][b];

    if (x)
        res -= at[x - 1][a][b];

    return res;
}

int get_distance(int x, int y)
{
    int cnt[3];
    for (int i = 0; i < 3; i++) {
        if (get_cnt(x, y, i, 0) != get_cnt(x, y, i, 1))
            return -1;

        cnt[i] = get_cnt(x, y, i, 0);
    }

    int swaps = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = i; j < 3; j++) {
            int s = min(get_swaps(x, y, i, j), get_swaps(x, y, j, i));
            cnt[i] -= s;

            if (i != j) {
                swaps += s;
                cnt[j] -= s;
            }
        }
    }

    if (cnt[0] != cnt[1] || cnt[0] != cnt[2])
        exit(EXIT_FAILURE);

    swaps += 2 * cnt[0];

    return swaps;
}