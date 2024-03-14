#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        string s;
        cin >> n;
        cin >> s;

        string good = "FBFFBFFBFBFFBFFBFB";

        bool isgood = false;
        for (int i = n; i < good.size() && !isgood; i++) {
            if (good.substr(i - n, n) == s)
                isgood = true;
        }   

        if (isgood)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}