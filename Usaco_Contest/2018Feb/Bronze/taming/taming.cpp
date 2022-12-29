#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int calendar[MAXN];
int n;

bool correct_prev_days(int day, int value)
{
    if (value == -1)
        return true;

    if (calendar[day] == value)
        return true;
    else if (calendar[day] == -1) {
        calendar[day] = value;
        return correct_prev_days(day - 1, value - 1);
    }
    else 
        return false;
}

int main(void)
{
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    scanf("%d", &n);
    bool consist = true;
    scanf("%d", &calendar[0]);
    if (calendar[0] != 0 && calendar[0] != -1)
        consist = false;
    calendar[0] = 0;

    for (int i = 1; i < n && consist; i++) {
        scanf("%d", &calendar[i]);
        if (calendar[i] != -1) 
            consist = correct_prev_days(i - 1, calendar[i] - 1);
    }

    int uncertain = 0;
    int certain = 0;
    for (int i = 0; i < n && consist; i++) {
        if (calendar[i] == 0)
            certain++;
        else if (calendar[i] == -1)
            uncertain++;
    }

    if (consist)
        printf("%d %d\n", certain, certain + uncertain);
    else 
        printf("-1\n");
    return 0;
}