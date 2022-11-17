/*
ID: panos.p1
LANG: C++
TASK: combo
*/

#include <bits/stdc++.h>

using namespace std;

int key_length;

int find_dist(int a, int b)
{
    return min((((a - b) % key_length) + key_length) % key_length, (((b - a) % key_length) + key_length) % key_length);
}

int main(void)
{
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);

    scanf("%d", &key_length);
    int first[3];
    int second[3];

    for (int i = 0; i < 3; i++)
        scanf("%d", &first[i]);
    for (int i = 0; i < 3; i++)
        scanf("%d", &second[i]);


    int mult_by = min(key_length, 5);
    int total_comb = 2 * mult_by * mult_by * mult_by;

    int dist1 = find_dist(first[0], second[0]);
    int dist2 = find_dist(first[1], second[1]);
    int dist3 = find_dist(first[2], second[2]);

    int mult1 = max(mult_by - dist1, 0) + max(mult_by - key_length + dist1, 0);
    int mult2 = max(mult_by - dist2, 0) + max(mult_by - key_length + dist2, 0);
    int mult3 = max(mult_by - dist3, 0) + max(mult_by - key_length + dist3, 0);

    int total_lost = mult1 * mult2 * mult3;

    printf("%d\n", total_comb - total_lost);
    return 0;
}