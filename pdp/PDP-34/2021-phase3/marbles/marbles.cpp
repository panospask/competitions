/*
USER: 34pdppaskp
LANG: C++
TASK: marbles
*/

#include <bits/stdc++.h>

using namespace std;

map<vector<int>, vector<int>> done_moves;
vector<int> line;

void bfs(vector<pair<int, int>> moves, int m, int n)
{
    queue<vector<int>> q;

    q.push(line);
    vector<int> vec;
    done_moves[line] = vec;

    while (!q.empty()) {
        auto tried_case = q.front();
        q.pop();
        vec = done_moves[tried_case];

        bool correct = true;
        for (int i = 1; i <= n; i++) {
            if (tried_case[i] != i) {
                correct = false;
                break;
            }
        }
        if (correct) {
            int size = vec.size();
            printf("MOVES %d\n", size);
            for (auto i : vec)
                printf("%d\n", i);
            return;
        }

        int i = 0;
        for (auto move : moves) {
            i++;
            swap(tried_case[move.first], tried_case[move.second]);
            if (done_moves.find(tried_case) == done_moves.end()) {
                vec.push_back(i);
                done_moves[tried_case] = vec;
                vec.pop_back();
                q.push(tried_case);
            }
            swap(tried_case[move.first], tried_case[move.second]);
        }
    }

    printf("IMPOSSIBLE\n");

}

int main(void)
{
    freopen("marbles.in", "r", stdin);
    freopen("marbles.out", "w", stdout);

    int t, n;
    cin >> t >> n;
    line.resize(n + 1);

    for (int x = 0; x < t; x++) {
        int m;
        scanf("%d", &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &line[i]);
        }
        vector<pair<int, int>> moves(m);
        int first, second;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &first, &second);
            moves[i].first = first;
            moves[i].second = second;
        }

        done_moves.clear();
        bfs(moves, m, n);
    }

}