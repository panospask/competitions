#include <bits/stdc++.h>

using namespace std;

string s;

int main(void) {
    cin >> s;

    int ans = 0;
    int c = 0;
    char p = '$';
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != p) {
            p = s[i];
            c = 0;
        }
        c++;

        ans = max(ans, c);
    }

    if (ans >= 7) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}