#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

#define pb push_back
#define mp make_pair

vector<ii> tied[20005][11];
bool can_used[20005][11];
int n, k;

void rem_num(int i, int var)
{
    if (can_used[i][var]) {
        can_used[i][var] = false;
        for (auto& p : tied[i][var]) {
            if (can_used[i][var])
                rem_num(i, var);
        }
        tied[i][var].clear();
    }
}

void q1(void)
{
    int i, x;
    scanf("%d%d", &i, &x);

    rem_num(i, x);
}

void q2(void)
{
    int i, j, x;
    bool can_exist = true;
}

int main(void)
{
    ; // 1-based-arr
}