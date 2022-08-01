/*
ID: panos.p1
LANG: C++11
TASK: camelot
*/

#include <bits/stdc++.h>
#define MAXN 30 * 30
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

vector<int> adj_list[MAXN];
vector<int> king_list[MAXN];
vector<int> knpos;
int distmoves[MAXN][MAXN];
int knightdist[MAXN];
int n, m;
int kingcost[MAXN];

void calc_moves_knight(void)
{
    for (int i = 0; i < n * m; i++)
        for (int j = 0; j < n * m; j++)
            distmoves[i][j] = -1;

    for (int i = 0; i < n * m; i++) {
        queue<int> q;
        distmoves[i][i] = 0;
        q.push(i);

        int cur;
        while (!q.empty()) {
            cur = q.front(); q.pop();
            for (auto neigh : adj_list[cur]) {
                if (distmoves[i][neigh] == -1) {
                    distmoves[i][neigh] = distmoves[i][cur] + 1;
                    q.push(neigh);
                }
            }
        }
    }    
}

void calc_moves_king(int kingpos)
{
    for (int i = 0; i < n * m; i++)
        kingcost[i] = -1;

    kingcost[kingpos] = 0;
    queue<int> q;
    q.push(kingpos);

    int cur;
    while (!q.empty()) {
        cur = q.front(); q.pop();

        for (auto neigh : king_list[cur])
            if (kingcost[neigh] == -1) {
                kingcost[neigh] = kingcost[cur] + 1;
                q.push(neigh);
            }
    }
}

int gather_king_at(int knight, int square, int dest)
{
    return distmoves[knight][square] + kingcost[square] + distmoves[square][dest];
}

void connect_to_knight(ii i, ii j)
{
    if (i.first >= 0 && i.first < n)
        if (i.second >= 0 && i.second < m)
            if (j.first >= 0 && j.first < n)
                if (j.second >= 0 && j.second < m) {
                    // CORD CONVERT
                    int first = ((n-1) - i.first) * m + i.second;
                    int second = ((n-1) - j.first) * m + j.second;
                    adj_list[first].push_back(second);
                }
}
void connect_to_king(ii i, ii j)
{
    if (i.first >= 0 && i.first < n)
        if (i.second >= 0 && i.second < m)
            if (j.first >= 0 && j.first < n)
                if (j.second >= 0 && j.second < m) {
                    // CORD CONVERT
                    int first = ((n-1) - i.first) * m + i.second;
                    int second = ((n-1) - j.first) * m + j.second;
                    king_list[first].push_back(second);
                }
}

void connect_square(int j) 
{
    ii i;
    i.first = j / m;
    i.second = j % m;

    connect_to_knight(i, mp(i.first - 2, i.second - 1));
    connect_to_knight(i, mp(i.first - 1, i.second - 2));
    connect_to_knight(i, mp(i.first - 2, i.second + 1));
    connect_to_knight(i, mp(i.first - 1, i.second + 2));
    connect_to_knight(i, mp(i.first + 1, i.second - 2));
    connect_to_knight(i, mp(i.first + 2, i.second - 1));
    connect_to_knight(i, mp(i.first + 1, i.second + 2));
    connect_to_knight(i, mp(i.first + 2, i.second + 1));
    connect_to_king(i, mp(i.first - 1, i.second - 1));
    connect_to_king(i, mp(i.first - 1, i.second));
    connect_to_king(i, mp(i.first - 1, i.second + 1));
    connect_to_king(i, mp(i.first, i.second - 1));
    connect_to_king(i, mp(i.first, i.second + 1));
    connect_to_king(i, mp(i.first + 1, i.second -1));
    connect_to_king(i, mp(i.first + 1, i.second));
    connect_to_king(i, mp(i.first + 1, i.second +1));

}

int main(void)
{
    freopen("camelot.in", "r", stdin);
    freopen("camelot.out", "w", stdout);

    scanf("%d %d", &n, &m);
    char col;
    int row;
    int truecol;
    int truerow;
    ii king;
    // read king
    scanf(" %c %d", &col, &row);
    truecol = col - 'A';
    truerow = n - row;
    int kingpos = truerow * m + truecol;
    king.first = truerow;
    king.second = truecol;

    //read knights
    int curpos;
    while (scanf(" %c %d", &col, &row) != EOF) {
        truecol = col - 'A';
        truerow = n - row;
        curpos = truerow * m + truecol;
        knpos.pb(curpos);
    }

    for (int i = 0; i < n * m; i++)
        connect_square(i);

    calc_moves_knight();
    calc_moves_king(kingpos);

    long long int sum = 0;
    long long int ans = LONG_LONG_MAX;
    for (int i = 0; i < n * m; i++) {
        sum = 0;
        bool check = true;
        for (auto k : knpos) {
            sum += distmoves[k][i];
            if (distmoves[k][i] == -1)
                check = false;
        }
        if (check) {
            ans = min(ans, sum + kingcost[i]);
            for (auto k : knpos) {
                sum -= distmoves[k][i];
                for (int j = max(0, king.first -2); j < n && j <= king.first + 2; j++) {
                    for (int l = max(0, king.second -2); l < m && l <= king.second + 2; l++) {
                        int sq = j * m + l;
                        if (distmoves[k][sq] != -1 && distmoves[sq][i] != -1)
                            ans = min(ans, sum + gather_king_at(k, sq, i));
                    }
                }
                sum += distmoves[k][i];
            }
        }
    }


    printf("%lld\n", ans);
    return 0;
}