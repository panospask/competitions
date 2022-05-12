#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    freopen("tennis.in", "r", stdin);
    freopen("tennis.out", "w", stdout);

    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {

        vector<int> matches_left;
        int n;
        cin >> n;

        int new_player;
        for (int j = 0; j < n; j++) {
            cin >> new_player;
            matches_left.push_back(new_player);
        }
        
        bool ispos = true;
        int elements = n;
        sort(matches_left.begin(), matches_left.end());
        while (elements > 0) {
            for (int i = n - elements; matches_left[i] == 0 && i < n; i++)
                elements--;
            if (!elements)
                break;

            int size = matches_left.size();
            int cur = size - 1;
            int to_remove = matches_left[cur];

            if (to_remove >= elements) {
                printf("Not possible\n");
                ispos = false;
                break;
            }
            else {
                for (int i = cur - 1, j = 0; j < to_remove; j++, i--) {
                    matches_left[cur]--;
                    matches_left[i]--;
                }
                elements--;
            }
        }
        if (ispos) {
            printf("Possible\n");
        }
    }
}