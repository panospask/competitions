/*
ID: panos.p1
LANG: C++
TASK: friday
*/

#include <bits/stdc++.h>

using namespace std;

int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int cnt[7] = {0};
int cur_day = 0;
int leaps = 0;

void sim_month(int i)
{
    cnt[(cur_day + 12) % 7]++;

    cur_day += months[i];
    cur_day %= 7;
}

void sim_year(int i)
{

    bool dis = false;

    if (i % 4 == 0) {
        if (i % 100 != 0) {
            dis = true;
            months[1]++;
            leaps++;
        }
        else {
            if (i % 400 == 0) {
                dis = true;
                months[1]++;
                leaps++;
            }
        }
    }

    for (int j = 0; j < 12; j++)
        sim_month(j);

    if (dis)
        months[1]--;
}

int main(void)
{
    freopen("friday.in", "r", stdin);
    freopen("friday.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 1900; i < 1900 + n; i++) 
        sim_year(i);

    for (int i = 0; i < 6; i++)
        printf("%d ", cnt[(i + 5) % 7]);
    printf("%d", cnt[4]);

    printf("\n");
}