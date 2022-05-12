#include <bits/stdc++.h>

using namespace std;


int num_of_cubes(bool** area, int n, int x_start, int y_start, int move_x, int move_y)
{
    if (x_start + move_x <= n && y_start + move_y <= n) {
        int x_end = x_start + move_x;
        int y_end = y_start + move_y;
        int cubes = 0;
        for (int i = x_start; i < x_end; i++)
            for (int j = y_start; j < y_end; j++)
                if (area[i][j])
                    cubes++;

        return cubes;
    }
    else {
        return 0;
    }
}

int find_max_in_area(bool** area, int n, int x, int y)
{

    int max_cubes = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int cubes = num_of_cubes(area, n, i, j, x, y);
            if (cubes > max_cubes)
                max_cubes = cubes;
        }

    return max_cubes;
}

int main(void)
{
    freopen("nered.in", "r", stdin);
    freopen("nered.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    bool** area;
    area = (bool**) malloc(sizeof(area) * n);
    for (int i = 0; i < n; i++) {
        area[i] = (bool*) malloc(sizeof(area) * n);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        area[x - 1][y - 1] = true;
    }

    int max_cubes = 0;
    for (int i = 1; i <= n && i <= m; i++) {
        if (m % i == 0) {
            int j = m / i;
            int cubes = find_max_in_area(area, n, i, j);
            if (cubes > max_cubes)
                max_cubes = cubes;
        }
    }

    int ans = m - max_cubes;
    cout << ans;
}