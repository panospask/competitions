#include <bits/stdc++.h>

using namespace std;

struct coordinates {
    int x;
    int y;
};
typedef struct coordinates Coordinates;

int main(void)
{

    freopen("test_input.in", "r", stdin);
    freopen("test_input.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    int map[n][m];
    bool visit[n][m] = {false};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> map[i][j];


    stack<Coordinates> my_stack;
    int islands = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (map[i][j]) 
                if (!visit[i][j]) {
                    visit[i][j];
                    Coordinates my_pair;
                    my_pair.x = i;
                    my_pair.y = j;

                    my_stack.push(my_pair);

                    while (my_stack.size() > 0) {
                        my_pair = my_stack.top();
                        my_stack.pop();

                        if (my_pair.x > 0) {
                            if (map[my_pair.x - 1][my_pair.y] && !visit[my_pair.x - 1][my_pair.y]) {
                                Coordinates new_pair;
                                new_pair.x = my_pair.x - 1;
                                new_pair.y = my_pair.y;
                                visit[new_pair.x][new_pair.y] = true;
                                my_stack.push(new_pair);
                            }
                        }
                        if (my_pair.y > 0) {
                            if (map[my_pair.x][my_pair.y - 1] && !visit[my_pair.x][my_pair.y - 1]) {
                                Coordinates new_pair;
                                new_pair.x = my_pair.x;
                                new_pair.y = my_pair.y - 1;
                                visit[new_pair.x][new_pair.y] = true;
                                my_stack.push(new_pair);
                            }
                        }
                        if (my_pair.y < m - 1) {
                            if (map[my_pair.x][my_pair.y + 1] && !visit[my_pair.x][my_pair.y + 1]) {
                                Coordinates new_pair;
                                new_pair.x = my_pair.x;
                                new_pair.y = my_pair.y + 1;
                                visit[new_pair.x][new_pair.y] = true;
                                my_stack.push(new_pair);
                            }
                        }
                        if (my_pair.x < n - 1) {
                            if (map[my_pair.x + 1][my_pair.y] && !visit[my_pair.x + 1][my_pair.y]) {
                                Coordinates new_pair;
                                new_pair.x = my_pair.x + 1;
                                new_pair.y = my_pair.y;
                                visit[new_pair.x][new_pair.y] = true;
                                my_stack.push(new_pair);
                            }
                        }
                    }
                    islands++;
                }
        } 

    cout << islands << endl;
}