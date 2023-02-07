#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

unordered_map<int, bool> isgood;
unordered_map<int, int> x1coords, x2coords, y1coords, y2coords;
set<int> seen;
int canvas[MAXN + 5][MAXN + 5];
int colnum[MAXN + 5][MAXN + 5];
int modby[MAXN + 5][MAXN + 5];

int n;

int main(void)
{
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &canvas[i][j]);
            if (canvas[i][j] == 0) continue;
            if (seen.find(canvas[i][j]) == seen.end()) {
                seen.insert(canvas[i][j]);
                isgood[canvas[i][j]] = true;
                x1coords[canvas[i][j]] = i;
                x2coords[canvas[i][j]] = i;
                y1coords[canvas[i][j]] = j;
                y2coords[canvas[i][j]] = j;
            }
            else {
                x1coords[canvas[i][j]] = min(x1coords[canvas[i][j]], i);
                x2coords[canvas[i][j]] = max(x2coords[canvas[i][j]], i);
                y1coords[canvas[i][j]] = min(y1coords[canvas[i][j]], j);
                y2coords[canvas[i][j]] = max(y2coords[canvas[i][j]], j);
            }
        }

    // We have the minimum rectangle of all the colours
    // Find the number of colours in each given point
    int x1, x2, y1, y2;
    for (auto colour : seen) {
        x1 = x1coords[colour];
        y1 = y1coords[colour];
        x2 = x2coords[colour];
        y2 = y2coords[colour];

        modby[x1][y1]++;
        modby[x1][y2 + 1]--;
        modby[x2 + 1][y1]--;
        modby[x2 + 1][y2 + 1]++;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) { 
            colnum[i][j] = colnum[i - 1][j] + colnum[i][j - 1] - colnum[i - 1][j - 1] + modby[i][j];

            if (colnum[i][j] > 1)
                isgood[canvas[i][j]] = false;
        }

    int ans = n * n - seen.size();
    for (auto colour : seen) {
        ans += isgood[colour];
    }

    // The special case where we only have one colour visible: it has to have painted over the others
    if (seen.size() == 1) ans = n * n - 1;

    printf("%d\n", ans);
    return 0;
}