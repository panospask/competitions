#include <bits/stdc++.h>

using namespace std;

vector<int> spot_in_line[100003];
bool visited[100003];
bool num_visited[100003];
int numbers[3][100003];
int indx[100003];
int counting[2][100003];
int ans = 0;

void bfs(int line)
{
    queue<int> q;
    q.push(line);

    while (!q.empty()) {
        int a = q.front(); q.pop();
        if (visited[a])
            continue;
        
        visited[a] = true;
        ans++;

        if (!--counting[0][numbers[1][a]])
            q.push(indx[numbers[1][a]]);
        if (!--counting[1][numbers[2][a]])
            q.push(indx[numbers[2][a]]);

        for (auto u : spot_in_line[numbers[0][a]])
            q.push(u);
        
    }

    
}

int main(void)
{
    freopen("physics.in", "r", stdin);
    freopen("physics.out", "w", stdout);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> numbers[0][i];
        indx[numbers[0][i]] = i;
    }

    for (int i = 1; i < 3; i++)
        for (int j = 1; j <= n; j++) {
            cin >> numbers[i][j];
            counting[i - 1][numbers[i][j]]++;
            spot_in_line[numbers[i][j]].push_back(j);
        }

    for (int i = 0; i < 2; i++) 
        for (int j = 1; j <= n; j++) {
            if (!counting[i][j] && !visited[indx[j]]) {
                bfs(indx[j]);
            }
        }

    cout << ans << endl;
    return 0;
}