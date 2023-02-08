#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(10e5)
#define MODBY 1000000007

using namespace std;

typedef pair<int, int> ii;

int n;
ii coords[MAXN + 5];
unordered_map<int, vector<int>> same_y;
unordered_map<int, vector<int>> same_x;
map<ii, int> point_to_num;
long long int vert_dist[MAXN + 5];
long long int hor_dist[MAXN + 5];
long long int sum;

void find_vert_dist(vector<int>& y_cords, int x_cord)
{
    sort(y_cords.begin(), y_cords.end());

    // Iterate downwards
    long long int dist = 0;
    int prevc = y_cords[0];
    for (int i = 1; i < y_cords.size(); i++) {
        dist += i * abs(y_cords[i] - prevc);
        dist %= MODBY;
        vert_dist[point_to_num[mp(x_cord, y_cords[i])]] += dist;
        prevc = y_cords[i];
    }

    // Iterate upwards
    dist = 0;
    prevc = y_cords[y_cords.size() - 1];
    for (int i = y_cords.size() - 2; i >= 0; i--) {
        dist += (y_cords.size() - i - 1) * abs(y_cords[i] - prevc);
        dist %= MODBY;
        vert_dist[point_to_num[mp(x_cord, y_cords[i])]] += dist;
        prevc = y_cords[i];
    }
}

void find_hor_dist(vector<int>& x_cords, int y_cord)
{
    sort(x_cords.begin(), x_cords.end());

    // Iterate downwards
    long long int dist = 0;
    int prevc = x_cords[0];
    for (int i = 1; i < x_cords.size(); i++) {
        dist += i * abs(x_cords[i] - prevc);
        dist %= MODBY;
        hor_dist[point_to_num[mp(x_cords[i], y_cord)]] += dist;
        prevc = x_cords[i];
    }

    // Iterate upwards
    dist = 0;
    prevc = x_cords[x_cords.size() - 1];
    for (int i = x_cords.size() - 2; i >= 0; i--) {
        dist += (x_cords.size() - i - 1) * abs(x_cords[i] - prevc);
        dist %= MODBY;
        hor_dist[point_to_num[mp(x_cords[i], y_cord)]] += dist;
        prevc = x_cords[i];
    }
}

int main(void)
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coords[i].first, &coords[i].second);
        same_x[coords[i].first].pb(coords[i].second);
        same_y[coords[i].second].pb(coords[i].first);

        point_to_num[coords[i]] = i;
    }

    // Find the sum of all vertical sides for all points
    for (auto vertline : same_x) 
        find_vert_dist(vertline.second, vertline.first);
    
    // Find the sum of all horizontal sides for all points
    for (auto horline : same_y)
        find_hor_dist(horline.second, horline.first);

    // Triangle area (hor * vert) / 2
    // We want double the area so we skip the /2
    long long int ttl_distance = 0;
    for (int i = 0; i < n; i++) {
        ttl_distance += ((hor_dist[i] % MODBY) * (vert_dist[i] % MODBY)) % MODBY;
        ttl_distance %= MODBY;
    }

    printf("%lld\n", ttl_distance);
    return 0;
}