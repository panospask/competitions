/*
ID: panos.p1
LANG: C++
TASK: milk2
*/

#include <bits/stdc++.h>

using namespace std;

int s[5005], t[5005];
int n;

int main(void)
{
    freopen("milk2.in", "r", stdin);
    freopen("milk2.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &s[i], &t[i]);

    sort(s, s + n);
    sort(t, t + n);

    int s_num = 0, t_num = 0;
    int cur_cows = 0;
    int max_milk = 0;
    int max_no_milk = 0;
    int cur_time = 0;
    bool milk_start = false;
    int latest_checkpoint = 0;

    while (s_num != n || t_num != n) {
        if (t_num == n || (s_num != n && s[s_num] <= t[t_num])) {
            if (!milk_start) {
                cur_cows++;
                cur_time = 0;
                latest_checkpoint = s[s_num];
                milk_start = true;
            }

            else {
                cur_time += s[s_num] - latest_checkpoint;
                cur_cows++;
                latest_checkpoint = s[s_num];
                if (cur_cows == 1) {
                    max_no_milk = max(max_no_milk, cur_time);
                    cur_time = 0;
                }
            }

            s_num++;
        }
        else {
            cur_time += t[t_num] - latest_checkpoint;
            cur_cows--;
            latest_checkpoint = t[t_num];
            if (cur_cows == 0) {
                max_milk = max(max_milk, cur_time);
                cur_time = 0;
            }

            t_num++;
        }
    }

    printf("%d %d\n", max_milk, max_no_milk);
    return 0;
}