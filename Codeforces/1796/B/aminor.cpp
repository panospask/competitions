#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    for (int x = 0; x < t; x++) {
        string a, b;
        cin >> a >> b;

        // Check if the first / last letters of a and b are the same
        bool isgood = false;
        if (a[0] == b[0]) {
            isgood = true;
            printf("YES\n%c*\n", a[0]);
        }
        if (!isgood && a[a.size() - 1] == b[b.size() - 1]) {
            isgood = true;
            printf("YES\n*%c\n", a[a.size() - 1]);
            continue;
        }

        // Find a substr that is length 2 and equal at a, b
        for (int i = 0; i < a.size() - 1 && !isgood; i++) {
            string cur = a.substr(i, 2);
            for (int j = 0; j < b.size() - 1 && !isgood; j++) {
                if (cur == b.substr(j, 2)) {
                    printf("YES\n*%c%c*\n", a[i], a[i + 1]);
                    isgood = true;
                    continue;
                }
            }
        }

        if (!isgood)
            printf("NO\n");
    }

    return 0;
}