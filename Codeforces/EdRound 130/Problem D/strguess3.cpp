#include <bits/stdc++.h>

using namespace std;

#define pb push_back

vector<int> in_cat[29];
int category[1005];
char catlet[29];
vector<int> last_oc;

char ask_char(int i) 
{
    printf("? 1 %d\n", i);
    fflush(stdout);

    getchar();
    char c = getchar();
    return c;
}

int ask_num(int l, int r)
{
    printf("? 2 %d %d\n", l, r);
    fflush(stdout);

    int num;
    scanf("%d", &num);
    return num;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    int cur_cat = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            category[i] = cur_cat;
            cur_cat++;
            catlet[category[i]] = ask_char(i);
            last_oc.pb(i);
        }
        else {
            int new_cat = ask_num(1, i);
            if (new_cat > cur_cat) {
                category[i] = cur_cat;
                cur_cat++;
                catlet[category[i]] = ask_char(i);
                last_oc.pb(i);
            }
            else {
                int r = last_oc.size();
                int l = 0;
                while (r - l > 1)  {
                    int m = (r + l) / 2;
                    int expect = cur_cat - m;
                    if (ask_num(last_oc[m], i) == expect) {
                        l = m;
                    }
                    else {
                        r = m;
                    }
                }


                int li = last_oc[l];
                category[i] = category[li];
                last_oc.pb(i);
                last_oc.erase(last_oc.begin() + l);
            }
        }
    }

    printf("! ");
    for (int i = 1; i <= n; i++) {
        printf("%c", catlet[category[i]]);
    }
    printf("\n");
    fflush(stdout);

    return 0;
}