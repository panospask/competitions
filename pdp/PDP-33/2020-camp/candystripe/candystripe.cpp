#include <bits/stdc++.h>

using namespace std;

struct stripe {
    int forw;
    int back;
    int max_st;
    int start;
};
typedef struct stripe Stripe;

Stripe init_str(int pos)
{
    Stripe str;
    str.start = pos;
    str.back = 0;
    str.forw = 1;
    str.max_st = pos;

    return str;
}

int main(void)
{
    freopen("candystripe.in", "r", stdin);
    freopen("candystripe.out", "w", stdout);
    
    int t;
    cin >> t;
    getchar();
    for (int i = 0; i < t; i++) {
        int pos = 1;
        int max_str = 0;
        list<Stripe> ls;
        char c;
        bool cont = false;
        for (c = getchar(); c != '\n' && c != EOF; c = getchar()) {
            if (c == 'S') {
                cont = false;
                if (ls.empty()) 
                    ls.push_back(init_str(pos));
                else {
                    auto li = ls.begin();
                    while (li != ls.end() && !cont) {
                        if (li->back >= -1) {
                            cont = true;
                            auto li_temp = li;
                            li_temp++;
                            ls.erase(li_temp, ls.end());
                            li->back = 0;
                            li->forw++;
                            li->max_st = pos;
                        }
                        else {
                            li->back++;
                            li->forw++;
                        }

                        li++;
                    }
                    if (!cont)
                        ls.push_back(init_str(pos));
                }
            }
            else {
                auto li = ls.begin();
                

                while (li != ls.end()) {
                    li->forw--;
                    li->back--;
                    if (li->forw < 0) {
                        auto li_t = li;
                        max_str = max(max_str , li->max_st - li->start + 1);
                        li++;
                        ls.erase(li_t);
                    }
                    else {
                        li++;
                    }
                }
            }
            pos++;
        }

        for (auto l : ls) {
            max_str = max( max_str, l.max_st - l.start + 1);
        }

        printf("%d\n", max_str);
    }
}