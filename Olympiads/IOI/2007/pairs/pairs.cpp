#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;

typedef pair<int, int> pi;

struct BITree {
    int size;
    vector<int> tree;

    void update(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }

    int get(int i) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }

    void init(int n) {
        size = n;
        tree.resize(size);
    }
};

struct BIT3D {
    int n, m, o;
    vector<vector<vector<int>>> tree;

    int g(int x) {return x & (x + 1);}
    int h(int x) {return x | (x + 1);}

    void add(int i, int j, int k, int v) {
        for (int x = i; x < n; x = h(x))
            for (int y = j; y < m; y = h(y))
                for (int z = k; z < o; z = h(z))
                    tree[x][y][z] += v;
    }

    // Get all in the subrectangle (0, 0) to (i, j)
    int get(int i, int j, int k) {
        int res = 0;
        for (int x = i; x >= 0; x = g(x) - 1)
            for (int y = j; y >= 0; y = g(y) - 1)
                for (int z = k; z >= 0; z = g(z) - 1)
                    res += tree[x][y][z];

        return res;
    }
    int get(int i1, int j1, int k1, int i2, int j2, int k2) {
        int ans = get(i2, j2, k2);

        ans -= get(i1 - 1, j2, k2);
        ans -= get(i2, j1 - 1, k2);
        ans -= get(i2, j2, k1 - 1);

        ans += get(i1 - 1, j1 - 1, k2);
        ans += get(i1 - 1, j2, k1 - 1);
        ans += get(i2, j1 - 1, k1 - 1);

        ans -= get(i1 - 1, j1 - 1, k1 - 1);

        return ans;
    }

    void init(int a, int b, int c) {
        n = a;
        m = b;
        o = c;
        tree.resize(a, vector<vector<int>>(b, vector<int>(c)));
    }
};

struct Point4D {
    int x, y, z, w;
};
struct Query4D {
    int x;
    int y1, y2;
    int z1, z2;
    int w1, w2;

    int mul;
};

bool operator < (const Point4D& a, const Point4D& b)
{
    return a.x < b.x;
}
bool operator < (const Query4D& a, const Query4D& b)
{
    return a.x < b.x;
}

int transform_x(int x, int y, int z)
{
    int res = x + y + z;
    return res;
}
int B, N, D, M;
int transform_y(int x, int y, int z)
{
    int res = x + y - z + M;
    return max(0, min(res, 3 * M));
}
int transform_z(int x, int y, int z)
{
    int res = x - y + z + M;
    return max(0, min(res, 3 * M));
}
int transform_w(int x, int y, int z)
{
    int res = x - y - z + 2 * M;
    return max(0, min(res, 3 * M));
}

Point4D transform(int x, int y, int z)
{
    return {transform_x(x, y ,z), transform_y(x, y, z), transform_z(x, y , z), transform_w(x, y, z)};
}

ll ans = 0;

void case1(void)
{
    vector<int> animals(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &animals[i]);
    sort(animals.begin(), animals.end());

    int l = 0;
    for (int r = 0; r < N; r++) {
        while (l < N && animals[r] - animals[l] > D) {
            l++;
        }

        ans += r - l;
    }

    printf("%lld\n", ans);
}

void case2(void)
{
    BITree plane;
    plane.init(2 * M + 1);

    vector<pair<pi, pi>> queries;
    vector<pi> points;

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        int x1 = x - D - y;
        int x2 = x + D - y;
        int y1 = x - D + y;
        y1 = max(y1, 0);
        int y2 = x + D + y;
        y2 = min(y2, 2 * M);
        int n_x = x - y;
        int n_y = x + y;

        points.push_back(mp(n_x, n_y));

        x1--;
        queries.push_back(mp(mp(x1, -1), mp(y1, y2)));
        queries.push_back(mp(mp(x2, +1), mp(y1, y2)));
    }

    sort(points.begin(), points.end());
    sort(queries.begin(), queries.end());

    int to_add = 0;
    for (auto q : queries) {
        while (to_add < N && points[to_add].first <= q.first.first) {
            plane.update(points[to_add].second, 1);
            to_add++;
        }

        ans += plane.get(q.second.first, q.second.second) * q.first.second;
    }

    ans = (ans - N) / 2;

    printf("%lld\n", ans);
}

void case3(void)
{
    BIT3D space;
    space.init(3 * M + 1, 3 * M + 1, 3 * M + 1);

    vector<Point4D> points;
    vector<Query4D> queries;

    for (int i = 0; i < N; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);

        points.push_back(transform(x, y, z));

        Point4D fir = transform(x - D, y, z);
        Point4D sec = transform(x + D, y, z);

        Query4D cur;
        cur.x = fir.x - 1;
        cur.y1 = fir.y;
        cur.z1 = fir.z;
        cur.w1 = fir.w;
        cur.y2 = sec.y;
        cur.z2 = sec.z;
        cur.w2 = sec.w;

        cur.mul = -1;
        queries.push_back(cur);

        cur.x = sec.x;
        cur.mul = 1;
        queries.push_back(cur);
    }

    sort(points.begin(), points.end());
    sort(queries.begin(), queries.end());

    int to_add = 0;
    for (auto q : queries) {
        while (to_add < N && points[to_add].x <= q.x) {
            space.add(points[to_add].y, points[to_add].z, points[to_add].w, 1);
            to_add++;
        }

        ans += space.get(q.y1, q.z1, q.w1, q.y2, q.z2, q.w2) * q.mul;
    }

    ans = (ans - N) / 2;

    printf("%lld\n", ans);
}

int main(void)
{
    scanf("%d %d %d %d", &B, &N, &D, &M);

    if (B == 1)
        case1();
    else if (B == 2)
        case2();
    else
        case3();

    return 0;
}