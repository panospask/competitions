#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

typedef pair<int, int> ii;

set<ii> cow_xs;
set<ii> cow_ys;

ii cows[MAXN];
int n;

void erase_cow(int cow)
{
    cow_xs.erase(mp(cows[cow].first, cow));
    cow_ys.erase(mp(cows[cow].second, cow));
}

void add_cow(int cow)
{
    cow_xs.insert(mp(cows[cow].first, cow));
    cow_ys.insert(mp(cows[cow].second, cow));
}

int find_opt_ans_removing_i_cows(int i)
{
    if (i == 0) {
        set<ii>::iterator it;
        it = cow_xs.begin();
        int x1 = (*it).first;
        it = cow_xs.end();
        it--;
        int x2 = (*it).first;
        int width = x2 - x1;

        it = cow_ys.begin();
        int y1 = (*it).first;
        it = cow_ys.end();
        it--;
        int y2 = (*it).first;
        int height = y2 - y1;

        return width * height; 
    }

    // Four cases : remove the downmost, upmost, leftmost, rightmost cow
    int ans = INT_MAX;
    set<ii>::iterator it;

    int curcow = (*cow_xs.begin()).second;
    erase_cow(curcow);
    ans = min(ans, find_opt_ans_removing_i_cows(i - 1));
    add_cow(curcow);

    it = cow_xs.end();
    it --;
    curcow = (*it).second;
    erase_cow(curcow);
    ans = min(ans, find_opt_ans_removing_i_cows(i - 1));
    add_cow(curcow);

    it = cow_ys.begin();
    curcow = (*it).second;
    erase_cow(curcow);
    ans = min(ans, find_opt_ans_removing_i_cows(i - 1));
    add_cow(curcow);

    it = cow_ys.end();
    it--;
    curcow = (*it).second;
    erase_cow(curcow);
    ans = min(ans, find_opt_ans_removing_i_cows(i - 1));
    add_cow(curcow);

    return ans;
}

int main(void)
{
    freopen("reduce.in", "r", stdin);
    freopen("reduce.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) { 
        scanf("%d %d", &cows[i].first, &cows[i].second);
        cow_xs.insert(mp(cows[i].first, i));
        cow_ys.insert(mp(cows[i].second, i));
    }


    int ans = find_opt_ans_removing_i_cows(3);
    printf("%d\n", ans);
    return 0;   
}