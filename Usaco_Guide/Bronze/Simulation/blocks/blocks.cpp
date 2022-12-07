#include <bits/stdc++.h>
#define MAXN 100
#define LETTERS 26

using namespace std;

int maxlet[LETTERS];
int curlet[2][LETTERS];
int n;

int main(void)
{
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);

    scanf("%d", &n);
    string a, b;
    for (int i = 0 ; i < n; i++) {
        for (int l = 0; l < LETTERS; l++) {
            curlet[0][l] = 0;
            curlet[1][l] = 0;
        }
        cin >> a >> b;
        for (auto c : a) {
            curlet[0][c - 'a']++;
        }
        for (auto c : b) {
            curlet[1][c - 'a']++;
        }

        for (int l = 0; l < LETTERS; l++) {
            maxlet[l] += max(curlet[0][l], curlet[1][l]);
        }
    }

    for (int l = 0; l < LETTERS; l++) {
        printf("%d\n", maxlet[l]);
    }
    return 0;
}