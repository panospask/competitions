#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

const int n = 9;
const int side = n / 3;

typedef pair<int, int> pi;
typedef long long ll;

const int DIRS = 2;
int dir[] = {1, side};

unordered_map<int, int> d;
int initial;
int target;
vector<pi> moves;
vector<int> npow;
vector<int> cur;

bool inbound(int i)
{
    return i >= 0 && i < n;
}

void decode(int code)
{
    for (int i = 0; i < n; i++) {
        cur[i] = code % n;
        code /= n;
    }
}

int main(void)
{
    npow.resize(n);
    cur.resize(n);

    int fact = 1;
    npow[0] = 1;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        initial += num * npow[i];
        target += i * npow[i];

        if (i != n - 1)
            npow[i + 1] = npow[i] * 9;
    }

    // Create the moves
    for (int i = 0; i < n; i++)
        for (int x = 0; x < DIRS; x++) {
            int ni = i + dir[x];
            if (inbound(ni) && (i % side == ni % side || i % side + 1 == ni % side))
                moves.push_back(mp(i, ni));
        }

    queue<int> q;
    d[initial] = 0;
    q.push(initial);

    int ans = 0;
    int totalcheck = 0;
    while (!q.empty()) {
        int code = q.front();
        q.pop();

        if (code == target) {
            ans = d[code];
            break;
        }

        decode(code);
        for (auto& p : moves) {
            ll nxt = code;
            nxt += cur[p.f] * (npow[p.s] - npow[p.f]);
            nxt += cur[p.s] * (npow[p.f] - npow[p.s]);
            if (d.find(nxt) == d.end()) {
                d[nxt] = d[code] + 1;
                q.push(nxt);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}