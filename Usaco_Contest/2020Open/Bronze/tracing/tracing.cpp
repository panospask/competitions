#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100
#define MAXT 250

using namespace std;

struct interaction {
    int time;
    int cow1;
    int cow2;
};
typedef struct interaction Interaction;

bool final_situation[MAXN + 2];
Interaction contacts[MAXT + 2];
int n, t;
int npossible = 0;
int maxk = 0;
int mink = INT_MAX;
bool infected[MAXN + 2];
int shakes_remaining[MAXN + 2];

bool operator < (Interaction a, Interaction b)
{
    return a.time < b.time;
}

void make_infected(int cow, int k)
{
    infected[cow] = true;
    shakes_remaining[cow] = k + 1;
}

bool test_sit(int pzero, int k)
{
    // Simulate a situation and find out if possible
    memset(infected, false, sizeof(infected));
    infected[pzero] = true;
    memset(shakes_remaining, 0, sizeof(shakes_remaining));
    shakes_remaining[pzero] = k;

    for (int con = 0; con < t; con++) {

        bool inf1 = infected[contacts[con].cow1];
        bool inf2 = infected[contacts[con].cow2];
        if (inf1 && !inf2 && shakes_remaining[contacts[con].cow1] > 0) {
            make_infected(contacts[con].cow2, k);
        }
        else if (!inf1 && inf2 && shakes_remaining[contacts[con].cow2] > 0) {
            make_infected(contacts[con].cow1, k);
        }

        shakes_remaining[contacts[con].cow1] = max(shakes_remaining[contacts[con].cow1]- 1, 0);
        shakes_remaining[contacts[con].cow2] = max(shakes_remaining[contacts[con].cow2]- 1, 0);
    }

    for (int i = 0; i < n; i++)
        if (infected[i] != final_situation[i])
            return false;

    return true;
}

int main(void)
{
    freopen("tracing.in", "r", stdin);
    freopen("tracing.out", "w", stdout);

    scanf("%d %d", &n, &t);
    int healthy;
    for (int i = 0; i < n; i++) {
        scanf("%1d", &healthy);
        final_situation[i] = healthy;
    }
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &contacts[i].time, &contacts[i].cow1, &contacts[i].cow2);
        contacts[i].cow1--;
        contacts[i].cow2--;
    }

    sort(contacts, contacts + t);
    for (int i = 0; i < n; i++) {
        bool isgood = false;
        int lmax = 0;
        int lmin = INT_MAX;

        for (int k = 0; k <= t; k++) {
            if (test_sit(i, k)) {
                isgood = true;
                lmax = max(lmax, k);
                lmin = min(lmin, k);
            }
        }

        npossible += isgood;
        maxk = max(maxk, lmax);
        mink = min(mink, lmin);
    }

    printf("%d ", npossible);
    printf("%d ", mink);
    if (maxk == t)
        printf("Infinity\n");
    else 
        printf("%d\n", maxk);

    return 0;
}