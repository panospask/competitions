/*
ID: panos.p1
LANG: C++11
TASK: milk4
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXQ 20005
#define MAXP 100

using namespace std;

int val[MAXP];
int q, p;
int MinDP[MAXQ];
int LastN[MAXQ]; // Size of biggest container used for MinDP
int Nused[MAXQ];
set<int> ans;

int comp(const void* a, const void* b)
{
    return *(int*) b - *(int*) a;
}

bool isbetter(int a, int b)
{
    while (a && b) {
        if (LastN[a] < LastN[b])
            return true;
        else if (LastN[b] < LastN[a])
            return false;

        a -= LastN[a] * Nused[a];
        b -= LastN[b] * Nused[b];
    }

    if (a)
        return false;

    return true;
}


void findminpals(void)
{
    for (int i = 0; i <= q; i++) {
        MinDP[i] = INT_MAX;
        LastN[i] = -1;
        Nused[i] = -1;
    }

    MinDP[0] = 0;

    for (int i = 0; i < p; i++) {
        int tempDP[MAXQ], tempLN[MAXQ], tempNU[MAXQ];

        for (int j = 0; j <= q; j++) {
            tempDP[j] = MinDP[j];
            tempLN[j] = LastN[j];
            tempNU[j] = Nused[j];
        }

        for (int j = val[i]; j <= q; j++) {
            int prev = j - val[i];

            if (tempDP[prev] != INT_MAX) { // We can reach j
                if (tempLN[prev] == val[i]) {
                    tempLN[j] = val[i];
                    tempDP[j] = tempDP[prev];
                    tempNU[j] = tempNU[prev] + 1;
                }

                if (tempLN[prev] != val[i]) {
                    tempLN[j] = val[i];
                    tempDP[j] = tempDP[prev] + 1;
                    tempNU[j] = 1;
                }

                if (MinDP[prev] < INT_MAX && ((MinDP[prev] + 1 < tempDP[j]) || (MinDP[prev] + 1 == tempDP[j] && isbetter(prev, j - tempNU[j] * tempLN[j])))) {
                    tempLN[j] = val[i];
                    tempDP[j] = MinDP[prev] + 1;
                    tempNU[j] = 1;
                }
            }
        }

        for (int j = val[i]; j <= q; j++) {
            if (tempDP[j] <= MinDP[j]) {
                MinDP[j] = tempDP[j];
                LastN[j] = tempLN[j];
                Nused[j] = tempNU[j];
            }
        }
    }
}

void find_ans(int a)
{
    if (a == 0)
        return;

    ans.insert(LastN[a]);
    find_ans(a - LastN[a] * Nused[a]);
}

int main(void)
{
    freopen("milk4.in", "r", stdin);
    freopen("milk4.out", "w", stdout);

    scanf("%d %d", &q, &p);
    for (int i = 0; i < p; i++) {
        scanf("%d", &val[i]);
    }

    qsort(val, p, sizeof(int), comp);

    findminpals();
    find_ans(q);

    printf("%d", (int)ans.size());
    for (auto pl : ans)
        printf(" %d", pl);
    printf("\n");

    return 0;
}