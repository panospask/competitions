#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

list<ii> neighbors[50][50];
ii belongs_to[50][50];
int total[50][50];
bool visited[50][50] = {{false}};

int node_count(ii origin, ii node)
{
    int i, j;
    tie(i, j) = node;

    visited[i][j] = true;
    belongs_to[i][j] = origin;

    int nodes = 1;
    for (auto const neigh : neighbors[i][j]) {
        int r, w;
        tie(r, w) = neigh;
        if (!visited[r][w])
            nodes += node_count(origin, neigh);
    }

    total[i][j] = nodes;
    return nodes;
}

int find_total(ii node)
{
    int i, j;
    tie(i, j) = node;
    tie(i, j) = belongs_to[i][j];

    return total[i][j];
}

int merge_neighbors(ii node1, ii node2)
{
    int i, j, k, l;
    tie(i, j) = node1;
    tie(k, l) = node2;

    if (belongs_to[i][j].first == belongs_to[k][l].first && belongs_to[i][j].second == belongs_to[k][l].second)
        return find_total(node1);
    
    return find_total(node1) + find_total(node2);
}

int main(void)
{
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int neigh;
            cin >> neigh;

            if (neigh % 2 == 0)
                neighbors[i][j].emplace_back(i, j - 1);

            if (neigh != 2 && neigh - 1 != 2 && neigh - 4 != 2 && neigh - 5 != 2 && neigh - 8 != 2 && neigh - 1 - 8 != 2 && neigh - 4 - 8 != 2 && neigh - 1 -4 - 8 != 2)
                neighbors[i][j].emplace_back(i - 1, j); 

            if (neigh != 4 && neigh - 1 != 4 && neigh - 2 != 4 && neigh - 3 != 4 && neigh - 8 != 4 && neigh - 1 - 8 != 4 && neigh - 2 - 8 != 4 && neigh - 1 -2 - 8 != 4)
                neighbors[i][j].emplace_back(i, j + 1); 

            if (neigh != 8 && neigh - 1 != 8 && neigh - 4 != 8 && neigh - 5 != 8 && neigh - 2 != 8 && neigh - 1 - 2 != 8 && neigh - 4 - 2 != 8 && neigh - 1 -4 - 2 != 8)
                neighbors[i][j].emplace_back(i + 1, j); 
        }
    }

    int max_space = 0;
    int room_num = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            if (!visited[i][j]) {
                room_num++;
                ii origin;
                origin.first = i;
                origin.second = j;
                int space = node_count(origin, origin);
                
                if (space > max_space)
                    max_space = space;
            }



    cout << room_num << '\n' << max_space << '\n';

    int max_merge = 0;
    int break_x, break_y;
    char coord;

    for (int j = 0; j < m; j++)
        for (int i = n - 1; i > 0; i--) {
            ii pair1 = make_pair(i, j);
            
            ii pair2 = pair1;
            pair2.first--;
            int merge1 = merge_neighbors(pair1, pair2);
            
            int merge2;
            if (j != m - 1) {
                pair2.first++; pair2.second++;
                merge2 = merge_neighbors(pair1, pair2);
            }
            else 
                merge2 = 0;

            if (merge1 > merge2) {
                if (merge1 > max_merge) {
                    max_merge = merge1;
                    break_x = i + 1;
                    break_y = j  + 1;
                    coord = 'N';
                }
            }
            else {
                if (merge2 > max_merge) {
                    max_merge = merge2;
                    break_x = i + 1;
                    break_y = j  + 1;
                    coord = 'E';
                }
            }
            
        }

    cout << max_merge << '\n' << break_x << ' ' << break_y << ' ' << coord << '\n';
}