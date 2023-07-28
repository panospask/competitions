#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

int H, W;
vector<vector<int>> paths;
vector<vector<bool>> blocked;

void add(int& a, int b)
{
    a += b;
    if (a > MOD)
        a -= MOD;
}

int main(void)
{
    scanf("%d %d", &H, &W);

    paths.resize(H, vector<int>(W));
    blocked.resize(H, vector<bool>(W));

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            char c;
            scanf(" %c", &c);

            blocked[i][j] = c == '#';
        }

    paths[0][0] = 1;
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            if (blocked[i][j])
                continue;

            if (i != H - 1)
                add(paths[i + 1][j], paths[i][j]);
            if (j != W - 1)
                add(paths[i][j + 1], paths[i][j]);
        }

    printf("%d\n", paths[H - 1][W - 1]);

    return 0;
}