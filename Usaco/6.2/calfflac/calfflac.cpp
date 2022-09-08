/*
ID: panos.p1
LANG: C++11
TASK: calfflac
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXS 20000

using namespace std;

string orig;
string proc;
int proc_to_orig[MAXS];
pair<int, int> ansspos;
int ans = 0;

// There is a palindrome from lpointer to rpointer
void check_pal(int lpointer, int rpointer)
{
    int prv = lpointer - 1;
    int nxt = rpointer + 1;

    int curans = rpointer - lpointer + 1;
    while (prv >= 0 && nxt < proc.size() && proc[prv] == proc[nxt]) {
        curans += 2;
        prv--;
        nxt++;
    }

    if (curans > ans) {
        ans = curans;
        ansspos = mp(prv + 1, nxt - 1);
    }
}

int main(void)
{
    freopen("calfflac.in", "r", stdin);
    freopen("calfflac.out", "w", stdout);   

    int i = 0;
    char c;
    while (true) {
        if (scanf("%c", &c) == EOF)
            break;
        orig.pb(c);
        
        i++;
    }

    int proci = 0;
    for (int i = 0; i < orig.size(); i++) {
        if (isalpha(orig[i])) {
            proc.pb(tolower(orig[i]));
            proc_to_orig[proci] = i;
            proci++;
        }
    }

    for (int i = 0; i < proc.size(); i++) {
        check_pal(i, i);
        if (proc[i] == proc[i+1])
            check_pal(i, i + 1);
    }


    pair<int, int> act_ans = mp(proc_to_orig[ansspos.first], proc_to_orig[ansspos.second]);

    printf("%d\n", ans);
    for (int i = act_ans.first; i <= act_ans.second; i++)
        putchar(orig[i]);
    printf("\n");
    return 0;    
}