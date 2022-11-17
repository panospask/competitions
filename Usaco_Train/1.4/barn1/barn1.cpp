/*
ID: panos.p1
LANG: C++
TASK: barn1
*/

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
typedef pair<int,int> ii;

int m, s, c;
bool stalls[205];
vector<ii> ans;

void solve_for(int i)
{
    if (i == 1) {
        int first_cover = -1, last_cover;
        for (int j = 0; j < s; j++)
            if (stalls[j]) {
                if (first_cover == -1)
                    first_cover = j;
                last_cover = j;
            }

        ans.pb(mp(first_cover, last_cover));
    }

    else {
        solve_for(i - 1);

        int max_first = -1;
        int max_last = -2;
        int max_spot = -1;

        int l = 0;
        for (auto plank : ans) {
            int cur_uncover;
            bool is_cur_cover = true;
            for (int i = plank.first; i <= plank.second; i++) {
                if (!stalls[i]) {
                    if (is_cur_cover) {
                        cur_uncover = i;
                        is_cur_cover = false;
                    }
                }
                else {
                    if (!is_cur_cover) {
                        is_cur_cover = true;
                        if (max_last - max_first < i - 1 - cur_uncover) {
                            max_last = i - 1;
                            max_first = cur_uncover;
                            max_spot = l;
                        }
                    }
                }
            }

            l++;
        }

        if (max_last - max_first + 1 > 0) {
            ii to_break = ans[max_spot];
            ans.erase(ans.begin() + max_spot);
            ans.pb(mp(to_break.first, max_first - 1));
            ans.pb(mp(max_last + 1, to_break.second));
        }
    }

    return;
}

int main(void)
{
    freopen("barn1.in", "r", stdin);
    freopen("barn1.out", "w", stdout);

    scanf("%d %d %d", &m, &s, &c);
    for (int i = 0; i < c; i++) {
        int num;
        cin >> num;

        stalls[num - 1] = true;
    }

    solve_for(m);

    int cnt = 0;
    for (auto plank : ans)
        cnt += plank.second - plank.first + 1;

    printf("%d\n", cnt);
    return 0;
}