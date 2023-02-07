#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 8
#define MAXK 10

using namespace std;

int original[MAXN][MAXN];
int pieces[MAXK][MAXN][MAXN];
int n, k;
int testing[MAXN][MAXN];

bool isgood_hor(int piece, int shift)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if ((j + shift >= n || j + shift < 0) && pieces[piece][i][j] == 1)
                return false;

    return true;
}

bool isgood_ver(int piece, int shift)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if ((i + shift >= n || i + shift < 0) && pieces[piece][i][j] == 1)
                return false;

    return true;
}

bool test_arrangement(int a, int h_a, int v_a, int b, int h_b, int v_b)
{
    memset(testing, 0, sizeof(testing));

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) {
            if (pieces[a][i][j] == 1)
                testing[i + v_a][j + h_a] += pieces[a][i][j];
            if (pieces[b][i][j] == 1)
                testing[i + v_b][j + h_b] += pieces[b][i][j];
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (testing[i][j] != original[i][j])
                return false;

    return true;
}

bool test_pieces(int a, int b)
{
    for (int h_a = -n + 1; h_a < n; h_a++) {
        if (!isgood_hor(a, h_a)) continue;
        for (int v_a = -n + 1; v_a < n; v_a++) {
            if (!isgood_ver(a, v_a)) continue;
            for (int h_b = -n + 1; h_b < b; h_b++) {
                if (!isgood_hor(b, h_b)) continue;
                for (int v_b = -n + 1; v_b < b; v_b++) {
                    if (!isgood_ver(b, v_b)) continue;

                    if (test_arrangement(a, h_a, v_a, b, h_b, v_b))
                        return true;
                }
            }
        }
    }
    return false;
}

int main(void)
{
    freopen("bcs.in", "r", stdin);
    freopen("bcs.out", "w", stdout);

    scanf("%d %d", &n, &k);
    char cur;
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < n; j++) {
            cur = getchar();
            original[i][j] = cur == '#';
        }
    }

    for (int x = 0; x < k; x++) {
            for (int i = 0; i < n; i++) {
            getchar();
            for (int j = 0; j < n; j++) {
                cur = getchar();
                pieces[x][i][j] = cur == '#';
            }
        }   
    }

    bool found = false;
    int f, s;
    for (int a = 0; a < k && !found; a++)
        for (int b = a + 1; b < k && !found; b++) {
            if (test_pieces(a, b)) {
                found = true;
                f = a + 1;
                s = b + 1;
            }
        }

    printf("%d %d\n", f, s);
    return 0;
}