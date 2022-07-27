/*
ID: panos.p1
LANG: C++11
TASK: spin
*/

#include <bits/stdc++.h>
#define MAXN 360
#define mp make_pair
#define MOD(i, j) ((i % j) + j) % j

using namespace std;

typedef pair<int, int> ii;

struct quad {
    int a;
    int b;
    int c;
    int d;

    quad(int i, int j, int k, int m) {
        a = i;
        b = j;
        c = k;
        d = m;    
    }
};
typedef struct quad Quad;

bool operator < (Quad i, Quad j)
{
    if (i.a == j.a) {
        if (i.b == j.b) {
            if (i.c == j.c)
                return i.d < j.d;
            return i.c < j.c;
        }
        return i.b < j.b;
    }
    return i.a < j.a;
}

ii wheels[5][5];
int speed[5];
int wedgenum[5];
map<Quad, bool> visited;
int ans = -1;

bool overlap(ii a, ii b)
{
    if (a.first > a.second) {
        return (overlap(mp(a.first, MAXN -1), b) || overlap(mp(0, a.second), b));
    }
    if (b.first > b.second) {
        return (overlap(a, mp(b.first, MAXN -1)) || overlap(a, mp(0, b.second)));
    }

    return (a.first <= b.second && b.first <= a.second);
}

int main(void)
{
    freopen("spin.in", "r", stdin);
    freopen("spin.out", "w", stdout);

    for (int i = 0; i < 5; i++) {
        scanf("%d", &speed[i]);
        scanf("%d", &wedgenum[i]);
        for (int j = 0; j < wedgenum[i]; j++) {
            scanf("%d %d", &wheels[i][j].first, &wheels[i][j].second);
            wheels[i][j].second += wheels[i][j].first;
            wheels[i][j].second = MOD(wheels[i][j].second, MAXN);
        }
    }

    ii first, second, third, fourth, fifth;
    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < wedgenum[0]; j++) {
            first = wheels[0][j];
            for (int k = 0; k < wedgenum[1]; k++) {
                second = wheels[1][k];
                if (overlap(first, second)) {
                    for (int l = 0; l < wedgenum[2]; l++) {
                        third = wheels[2][l];
                        if (overlap(third, first) && overlap(third, second)) {
                            for (int m = 0; m < wedgenum[3]; m++) {
                                fourth = wheels[3][m];
                                if (overlap(fourth, first) && overlap(fourth, second) && overlap(fourth, third)) {
                                    for (int n = 0; n < wedgenum[4]; n++) {
                                        fifth = wheels[4][n];
                                        if (overlap(fifth, first) && overlap(fifth, second) && overlap(fifth, third) && overlap(fifth, fourth)) {
                                            printf("%d\n", i);
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        for (int i = 0; i < 5; i++)
            for (int j = 0; j < wedgenum[i]; j++) {
                wheels[i][j].first = MOD(wheels[i][j].first + speed[i], MAXN);
                wheels[i][j].second = MOD(wheels[i][j].second + speed[i], MAXN);
            }
    }

    printf("none\n");
    return 0;
}