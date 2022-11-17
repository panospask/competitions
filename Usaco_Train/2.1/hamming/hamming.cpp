/*
ID: panos.p1
LANG: C++
TASK: hamming
*/

#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

using namespace std;

int n, b, d;
vector<int> codes;
int found = 0;

int hamming_dist(int a, int c)
{
    int dist = 0;
    for (int i = 0; i < b; i++) {
        dist += (CHECK_BIT(a, i) != CHECK_BIT(c, i));
    }

    return dist;
}

bool check_hamming(int num)
{
    for (auto& test : codes) {
        if (hamming_dist(test, num) < d)
            return false;
    }

    return true;
}

int main(void)
{
    freopen("hamming.in", "r", stdin);
    freopen("hamming.out", "w", stdout);

    scanf("%d %d %d", &n, &b, &d);

    int max_num = pow(2, b);

    for (int i = 0; i < max_num && found < n; i++) {
        if (check_hamming(i)) {
            found++;
            codes.push_back(i);
        }
    }

    int i = 1;
    int j = 1;
    for (auto& num : codes) {
        if (i == 10) {
            printf("%d\n", num);
            i = 1;
        }
        else if (j == n) {
            printf("%d\n", num);
        }
        else {
            printf("%d ", num);
            i++;
        }

        j++;
    }
    return 0;
}