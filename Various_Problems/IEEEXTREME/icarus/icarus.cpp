#include <bits/stdc++.h>

using namespace std;

int N, A, B;
string s;

int main(void)
{
    cin >> s;

    N = 2 * s.size();
    A = 1;
    B = N;

    int down = 0, up = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'L') {
            down++;
        }
        else if (s[i] == 'U') {
            up++;
        }
    }
    if (down > up) {
        swap(A, B);
    }

    printf("%d %d %d\n", N, A, B);

    for (int i = 0; i < N - 1; i++) {
        printf("%d %d\n", i + 2, 0);
    }
    printf("%d %d\n", 0, 0);

    return 0;
}