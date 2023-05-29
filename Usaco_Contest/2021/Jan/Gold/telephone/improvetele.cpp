#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n, k;
vector<int> breed;
vector<vector<int>> dist;
vector<vector<int>> friends;

int main(void)
{
    scanf("%d %d", &n, &k);

    breed.resize(n);
    dist.assign(k + 1, vector<int>(n, -1));
    friends.resize(k + 1, vector<int>(k + 1));

    for (int i = 0; i < n; i++) {
        scanf("%d", &breed[i]);
        breed[i]--;
    }
    for (int b1 = 0; b1 < k; b1++)
        for (int b2 = 0; b2 < k; b2++)
            scanf("%1d", &friends[b1][b2]);

    // Create fake breed for n - 1
    for (int b = 0; b < k; b++) {
        friends[b][k] = friends[b][breed[n-1]];
        friends[k][b] = friends[breed[n-1]][b];
    }
    breed[n-1] = k;

    deque<pi> q;
    dist[breed[0]][0] = 0;
    q.push_back(mp(breed[0], 0));

    int ans = -1;
    while (!q.empty()) {
        int senderbreed, cur;

        tie(senderbreed, cur) = q.front();
        q.pop_front();

        int currentbreed = breed[cur];

        if (senderbreed == breed[n - 1] && cur == n - 1) {
            // The message has arrived!
            ans = dist[senderbreed][cur];
            break;
        }

        if (friends[senderbreed][currentbreed]) {
            if (dist[currentbreed][cur] == -1) {
                dist[currentbreed][cur] = dist[senderbreed][cur];
                q.push_front(mp(currentbreed, cur));
            }
        }
        if (cur > 0 && dist[senderbreed][cur - 1] == -1) {
            dist[senderbreed][cur - 1] = dist[senderbreed][cur] + 1;
            q.push_back(mp(senderbreed, cur - 1));
        }
        if (cur < n - 1 && dist[senderbreed][cur + 1] == -1) {
            dist[senderbreed][cur + 1] = dist[senderbreed][cur] + 1;
            q.push_back(mp(senderbreed, cur + 1));
        }
    }

    printf("%d\n", ans);
    return 0;
}