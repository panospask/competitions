#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define N 7
#define MAXM 100

using namespace std;

typedef pair<int, string> istr;

map<string, int> cows;
int m;

void init_cows(void)
{
    cows["Bessie"] = 0;
    cows["Elsie"] = 0;
    cows["Daisy"] = 0;
    cows["Gertie"] = 0;
    cows["Annabelle"] = 0;
    cows["Maggie"] = 0;
    cows["Henrietta"] = 0;
}

int main(void)
{
    freopen("notlast.in", "r", stdin);
    freopen("notlast.out", "w", stdout);

    scanf("%d", &m);
    init_cows();

    string cow;
    int milk;
    for (int i = 0; i < m; i++) {
        cin >> cow >> milk;
        cows[cow] += milk;
    }

    set<istr> num_to_cows;
    for (const auto& cowval : cows) 
        num_to_cows.insert(mp(cowval.second, cowval.first));

    int i = 0;
    int prevmilk = 0;
    bool found_cow = false;
    int goodmilk = 0;
    string ans = "Tie";
    for (const auto& milkprod : num_to_cows) {
        if (!found_cow) {
            if (i == 0) {
                prevmilk = milkprod.first;
            }
            else if (milkprod.first != prevmilk) {
                ans = milkprod.second;
                goodmilk = milkprod.first;
                found_cow = true;
            }
        }
        else {
            if (milkprod.first == goodmilk) 
                ans = "Tie";
            break;
        }

        i++;
    }

    cout << ans << endl;
    return 0;
}