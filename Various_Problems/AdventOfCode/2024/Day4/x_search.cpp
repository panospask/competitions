#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const string TARGET = "MAS";

int N, M;
vector<string> text;

bool inside(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M;
}

bool test(int i, int j, int d_i, int d_j)
{
    for (int w = 0; w < TARGET.size(); w++) {
        if (!inside(i, j) || text[i][j] != TARGET[w]) {
            return false;
        }

        i += d_i;
        j += d_j;
    }

    return true;
}

bool is_x(int i, int j)
{
    if (text[i][j] != 'A') {
        return false;
    }

    int cnt = 0;
    for (int d_i = -1; d_i <= 1; d_i += 2) {
        for (int d_j = -1; d_j <= 1; d_j += 2) {
            cnt += test(i - d_i, j - d_j, d_i, d_j);
        }
    }

    return cnt >= 2;
}

int main(void)
{
    freopen("x_search.in", "r", stdin);
    freopen("x_search.out", "w", stdout);

    while (!cin.eof()) {
        string cur;
        getline(cin, cur);
        text.pb(cur);
    }

    N = text.size();
    M = text[0].size();

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ans += is_x(i, j);
        }
    }

    printf("%d\n", ans);

    return 0;
}