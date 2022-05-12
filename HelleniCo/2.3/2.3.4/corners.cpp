#include <bits/stdc++.h>

using namespace std;

int direction_i[4] = {-1, 0, +1, 0};
int direction_j[4] = {0, -1, 0, +1};

vector<pair<int,int>> start = {{4, 4}, {4, 5}, {5, 4}, {5, 5}}, win = {{0, 0}, {0 , 1}, {1, 0}, {1, 1} };
map<vector<pair<int,int>>, int> dist, visited;

char board[6][6];

void print_situation(vector<pair<int,int>> sit)
{
    for (auto coords : sit) {
        fprintf(stderr, "(%d,%d) ", coords.first, coords.second);
    }
    fprintf(stderr, "\n");
}

void bfs(void)
{
    queue<vector<pair<int,int>>> q;
    dist[start] = 0;
    visited[start] = 1;
    q.push(start);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        // print_situation(v);
        // cerr << q.size() << '\n';

        for (auto check : v) {
            board[check.first][check.second] = 'c';
        }

        for (int i = 0; i < 4; i++) {

            for (int k = 0; k < 4; k++) {
                auto temp = v;

                char adj1 = '\0', adj2 = '\0';
                if (temp[i].first + direction_i[k] >= 0 && temp[i].first + direction_i[k] < 6 && temp[i].second + direction_j[k] >= 0 && temp[i].second + direction_j[k] < 6)
                    adj1 = board[temp[i].first + direction_i[k]][temp[i].second + direction_j[k]];
                if (temp[i].first + 2 * direction_i[k] >= 0 && temp[i].first + 2 * direction_i[k] < 6 && temp[i].second + direction_j[k] * 2 >= 0 && temp[i].second + direction_j[k] * 2 < 6)
                    adj2 = board[temp[i].first + direction_i[k] * 2][temp[i].second + direction_j[k] * 2];

                if (adj1 == '.')
                    temp[i] = {temp[i].first + direction_i[k], temp[i].second + direction_j[k]};
                else if ((adj1 == 'c' || adj1 == 's') && adj2 == '.') {
                    temp[i] = {temp[i].first + 2 * direction_i[k], temp[i].second + 2 * direction_j[k]};
                }

                sort(temp.begin(), temp.end());

                if (!visited[temp]) {
                    q.push(temp);
                    dist.insert(make_pair(temp, dist[v] + 1));
                    visited[temp] = true;
                    if (temp == win) {
                        return;
                    }
                }
            }
        }

        for (auto pawn : v) {
            board[pawn.first][pawn.second] = '.';
        }
    }
}

int main(void)
{
    freopen("corners.in", "r", stdin);
    freopen("corners.out", "w", stdout);

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            cin >> board[i][j];

    bfs();

    if (dist[win] != 0)
        cout << dist[win];
    else 
        cout << -1;
    
    cout << endl;
}