/*
ID: panos.p1
LANG: C++11
TASK: hidden
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int failurefunc[2 * MAXN + 1];
string str;
int n;

// Returns the starting index of the minimal rotation of the string
int calc_best_rotation(void)
{
    str += str;
    for (int i = 0; i < str.size(); i++)
        failurefunc[i] = -1;
    
    int rotation = 0;
    for (int q = 1; q < str.size(); q++) {
        int i = failurefunc[q - 1 - rotation];

        while (i != -1 && str[rotation + i + 1] != str[q]) {
            if (str[q] < str[rotation + i + 1])
                rotation = q - i - 1;
            
            i = failurefunc[i];
        }

        if (i == -1 && str[rotation + i + 1] != str[q]) {
            if (str[q] < str[rotation + i + 1])
                rotation = q - i - 1;
            failurefunc[q - rotation] = -1;
        }
        else
            failurefunc[q - rotation] = i + 1;
    }

    return rotation % (str.size() / 2);
}

int main(void)
{
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);

    scanf("%d", &n);
    char c;
    for (int i = 0; i < n; i++) {
        if (!(i % 72))
            getchar();
        c = getchar();
        str.pb(c);
    }

    int pos = calc_best_rotation();
    printf("%d\n", pos);
}