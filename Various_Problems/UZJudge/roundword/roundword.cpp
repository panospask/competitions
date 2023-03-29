#include <bits/stdc++.h>
#define MAXN 2000

using namespace std;

int n, m;
// LCS of [n...n-i+1] and [1...j]
int rev_a[MAXN + 2][MAXN + 2];

// LCS of [1...i] and [m...m-j+1]
int rev_b[MAXN + 2][MAXN + 2];

string a;
string b;

int main(void)
{
    cin >> a >> b;

    n = a.size();
    m = b.size();
    a.push_back(a[n-1]);
    for (int i = n - 1; i > 0; i--)
        a[i] = a[i-1];
    a[0] = '\0';
    b.push_back(b[m-1]);
    for (int i = m - 1; i > 0; i--)
        b[i] = b[i-1];

    reverse(a.begin(), a.end());
    rev_a[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i] != b[j])
                rev_a[i][j] = max(rev_a[i-1][j], rev_a[i][j-1]);
            else 
                rev_a[i][j] = rev_a[i-1][j-1] + 1;
        }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    rev_b[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i] != b[j]) 
                rev_b[i][j] = max(rev_b[i-1][j], rev_b[i][j-1]);
            else 
                rev_b[i][j] = rev_b[i-1][j-1] + 1;
        }

    return 0;
}