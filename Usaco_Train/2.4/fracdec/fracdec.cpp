/*
ID: panos.p1
LANG: C++11
TASK: fracdec
*/

#include <bits/stdc++.h>
#define MAXDIV 100000
#define pb push_back

using namespace std;

int used_to[MAXDIV * 11];
vector<int> curdiv;
vector<int> ans;
int repstart = -1;

int n, d;

void find_division(int number, int div, int i)
{
    if (used_to[number] != -1) {
        repstart = used_to[number];
        ans = curdiv;

        return;
    }

    used_to[number] = i;

    curdiv.pb(number / div);

    if (number % div != 0) {
        int cur = number % div;
        cur *= 10;

        find_division(cur, div, i + 1);
    }
    else {
        ans = curdiv;
        return;
    }
}

int find_length(int i)
{
    int l = 0;
    while (i > 0) {
        i /= 10;
        l++;
    }

    return max(l, 1);
}

int main(void)
{
    freopen("fracdec.in", "r", stdin);
    freopen("fracdec.out", "w", stdout);

    scanf("%d %d", &n, &d);

    printf("%d.", n / d);

    for (int i = 0; i <= d * 10; i++)
        used_to[i] = -1;

    int mod_by = find_length(n / d) + 1;
    if (n % d == 0)
        printf("0");
    else {
        int c = n % d;
        c *= 10;
        find_division(c, d, 0);
        int i = 0;
        for (auto x : ans) {
            if ((i + 1 + mod_by) % 76 == 0 && i != 0)
                printf("\n");

            if (repstart == i)
                printf("(");
            printf("%d", x);
            i++;
        }
        if (repstart != -1)
            printf(")");
        
    }

    printf("\n");
    return 0;
}