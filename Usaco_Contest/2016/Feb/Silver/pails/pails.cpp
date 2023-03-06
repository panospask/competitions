#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXK 100

using namespace std;

typedef pair<int, int> ii;

int x, y, m, k;

queue<pair<ii, int>> states;
map<ii, bool> visited;
int moves_left;

bool tested(int i, int j)
{
    return visited[mp(i,j)];
}

void insert(int i, int j)
{
    visited[mp(i,j)] = true;
    states.push(mp(mp(i,j), moves_left));
}

int main(void)
{
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);

    scanf("%d %d %d %d", &x, &y, &k, &m);

    int i, j;

    int ans = INT_MAX;
    int test_i, test_j;

    moves_left = k;
    insert(0, 0);

    while (!states.empty()) {
        tie(i,j) = states.front().first;
        moves_left = states.front().second;
        states.pop();

        ans = min(ans, abs(i + j - m));

        if (moves_left == 0)
            continue;

        moves_left--;
        // Empty buckets
        // Bucket 1
        test_i = 0;
        test_j = j;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }
        // Bucket 2
        test_i = i;
        test_j = 0;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }

        // Fill buckets
        // Bucket 1
        test_i = x;
        test_j = j;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }
        // Bucket 2
        test_i = i;
        test_j = y;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }

        // Pour one in other
        // B1 --> B2
        int to_rm = min(i, y - j);
        test_i = i - to_rm;
        test_j = j + to_rm;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }
        // B2 --> B1
        to_rm = min(x - i, j);
        test_i = i + to_rm;
        test_j = j - to_rm;
        if (!tested(test_i, test_j)) {
            insert(test_i, test_j);
        }
    }

    printf("%d\n", ans);
    return 0;
}