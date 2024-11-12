#include <bits/stdc++.h>

using namespace std;

int N;
string s;

int main(void)
{
    cin >> s;

    N = s.size();

    int aces = 0;
    long long inversions = 0;
    for (int i = 0; i < N; i++) {
        if (s[i] == '1') {
            aces++;
        }
        else {
            inversions += aces;
        }
    }

    if (inversions % 3 == 0) {
        printf("Bob\n");
    }
    else {
        printf("Alice\n");
    }
}