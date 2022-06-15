/*
ID: panos.p1
LANG: C++
TASK: transform
*/

#include <bits/stdc++.h>

using namespace std;

char pattern[11][11];
char cor_pat[11][11];
bool used[11][11];
int n;

bool match_pattern(void)
{
    bool good = true;

    for (int i = 0; i < n && good; i++)
        for (int j = 0; j < n && good; j++)
            if (pattern[i][j] != cor_pat[i][j])
                good = false;

    return good;
}

void rotate_ninety(void)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            used[i][j] = false;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (!used[i][j]) {
                swap(pattern[i][j], pattern[j][n - i - 1]);
                used[i][j] = true;
                used[j][n - i - 1] = true;
            } 
        } 

    return;
}

void flip(void)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            used[i][j] = false;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (!used[i][j]) {
                swap(pattern[i][j],pattern[i][n - j - 1]);
                used[i][j] = true;
                used[i][n - j - 1] = true;
            }
        }

    return;
}

int main(void)
{
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            pattern[i][j] = getchar();
        getchar();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cor_pat[i][j] = getchar();
        getchar();
    }

    //Test case 1:
    rotate_ninety();
    if (match_pattern()) {
        printf("1\n");
        return 0;
    }

    //Test case 2:
    rotate_ninety();
    if (match_pattern()) {
        printf("2\n");
        return 0;
    }

    //Test case 3:
    rotate_ninety();
    if (match_pattern()) {
        printf("3\n");
        return 0;
    }

    //Test case 4:
    rotate_ninety();
    flip();
    if (match_pattern()) {
        printf("4\n");
        return 0;
    }

    //Test case 5:
    bool isgood = false;
    rotate_ninety();
    if (match_pattern())
        isgood = true;
    rotate_ninety();
    if (match_pattern())
        isgood = true;
    rotate_ninety();
    if (match_pattern())
        isgood = true;
    if (isgood) {
        printf("5\n");
        return 0;
    }

    //Test case 6:
    rotate_ninety();
    flip();
    if (match_pattern()) {
        printf("6\n");
        return 0;
    }

    //Test case 7:
    printf("7\n");
    return 0;
}