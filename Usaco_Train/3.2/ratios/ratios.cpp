/*
ID: panos.p1
LANG: C++11
TASK: ratios
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct trip
{
    int a = 0;
    int b = 0;
    int c = 0;

    trip (void) {
        a = 0;
        b = 0;
        c = 0;
    }
};
typedef struct trip Trip;
typedef pair<Trip, Trip> TT;


bool operator < (const trip a, const trip b) 
{   
    if (a.a == b.a) {
        if (a.b == b.b)
            return a.c < b.c;
        return a.b < b.b;
    }
    return a.a < b.a;
}

int goal[3];
int mixtures[3][3];
map<Trip, bool> visited;

Trip ans;

void bfs(void)
{
    queue<Trip> q;

    Trip start;
    q.push(start);

    bool goodcheck[3];
    Trip cur;
    Trip vals;
    while (!q.empty()) {
        cur = q.front(); q.pop();
        vals.a = mixtures[0][0] * cur.a + mixtures[1][0] * cur.b + mixtures[2][0] * cur.c;
        vals.b = mixtures[0][1] * cur.a + mixtures[1][1] * cur.b + mixtures[2][1] * cur.c;
        vals.c = mixtures[0][2] * cur.a + mixtures[1][2] * cur.b + mixtures[2][2] * cur.c;

        if (cur.a > 100 || cur.b > 100 || cur.c > 100) {
            continue;
        }
        
        
        goodcheck[0] = ((goal[0] == 0 && vals.a == 0) || (goal[0] != 0 &&(vals.a != 0 && vals.a % goal[0] == 0)));
        goodcheck[1] = ((goal[1] == 0 && vals.b == 0) || (goal[1] != 0 &&(vals.b != 0 && vals.b % goal[1] == 0)));
        goodcheck[2] = ((goal[2] == 0 && vals.c == 0) || (goal[2] != 0 &&(vals.c != 0 && vals.c % goal[2] == 0)));
        if (goodcheck[0] && goodcheck[1] && goodcheck[2]) {
            int divby = -1;
            bool isgood = true;
            int curdiv;
            // Check A:
            if (goal[0] != 0 && isgood) {
                curdiv = vals.a / goal[0];
                if (curdiv != divby) {
                    if (divby == -1)
                        divby = curdiv;
                    else 
                        isgood = false;
                }
            }
            // Check B:
            if (goal[1] != 0 && isgood) {
                curdiv = vals.b / goal[1];
                if (curdiv != divby) {
                    if (divby == -1)
                        divby = curdiv;
                    else 
                        isgood = false;
                }
            }
            // Check C:
            if (goal[2] != 0 && isgood) {
                curdiv = vals.c / goal[2];
                if (curdiv != divby) {
                    if (divby == -1)
                        divby = curdiv;
                    else 
                        isgood = false;
                }
            }

            if (isgood) {
                ans = cur;
                return;
            }
        }

        // ADD MIX 1
        if (cur.a < 99) {
            cur.a++;
            vals.a += mixtures[0][0]; vals.b += mixtures[0][1]; vals.c += mixtures[0][2];
            if (!visited[vals]) {
                visited[vals] = true;
                q.push(cur);
            }
            vals.a -= mixtures[0][0]; vals.b -= mixtures[0][1]; vals.c -= mixtures[0][2];
            cur.a--;
        }

        //ADD MIX 2
        if (cur.b < 99) {
            cur.b++;
            vals.a += mixtures[1][0]; vals.b += mixtures[1][1]; vals.c += mixtures[1][2];
            if (!visited[vals]) {
                visited[vals] = true;
                q.push(cur);
            }
            vals.a -= mixtures[1][0]; vals.b -= mixtures[1][1]; vals.c -= mixtures[1][2];
            cur.b--;
        }

        //ADD MIX 3
        if (cur.c < 99) {
            cur.c++;
            vals.a += mixtures[2][0]; vals.b += mixtures[2][1]; vals.c += mixtures[2][2];
            if (!visited[vals]) {
                visited[vals] = true;
                q.push(cur);
            }
            vals.a -= mixtures[2][0]; vals.b -= mixtures[2][1]; vals.c -= mixtures[2][2];
            cur.c--;
        }
    }

    start.a = -1;
    ans = start;
    return;
}

int main(void)
{
    freopen("ratios.in", "r", stdin);
    freopen("ratios.out", "w", stdout);

    for (int i = 0; i < 3; i++)
        scanf("%d", &goal[i]);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &mixtures[i][j]);

    bfs();
    if (ans.a == -1)
        printf("NONE\n");
    else {
        Trip vals;
        vals.a = mixtures[0][0] * ans.a + mixtures[1][0] * ans.b + mixtures[2][0] * ans.c;
        vals.b = mixtures[0][1] * ans.a + mixtures[1][1] * ans.b + mixtures[2][1] * ans.c;
        vals.c = mixtures[0][2] * ans.a + mixtures[1][2] * ans.b + mixtures[2][2] * ans.c;
        int ansnum;
        if (goal[0] != 0)
            ansnum = vals.a / goal[0];
        else if (goal[1] != 0)
            ansnum = vals.b / goal[1];
        else 
            ansnum = vals.c / goal[2];
        printf("%d %d %d %d\n", ans.a, ans.b, ans.c, ansnum);
    }

    return 0;
}

