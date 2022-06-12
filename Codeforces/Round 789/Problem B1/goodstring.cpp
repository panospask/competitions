#include <bits/stdc++.h>

using namespace std;

#define pb push_back

int str[200000];
vector<int> length;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);
        length.clear();

        int prev = -1;
        int prevnum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%1d", &str[i]);
            if (str[i] != prev) {
                if (prev != -1) {
                    length.pb(prevnum);
                    prevnum = 0;
                }
                prev = str[i];
            }
            prevnum++;
        }
        length.pb(prevnum);

        bool have_odd = false;
        int swaps = 0;
        int i = 0;
        bool recent_merge = false;
        int segments = length.size();
        for (auto substr : length) {
            if (have_odd)
                swaps++;
            if (substr % 2 == 1) { //Odd
                if (have_odd)
                    have_odd = false;
                else 
                    have_odd = true;

                if (substr == 1) {

                }
            }
            i++;
        }

        printf("%d %d\n", swaps, segments);
    }
    return 0;
}