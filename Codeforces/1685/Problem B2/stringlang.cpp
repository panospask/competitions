#include <bits/stdc++.h>

using namespace std;

#define pb push_back

vector<string> type3, type2, type1;
int n;
int pairs_remaining_2, pairs_remaining_3;
int spot_2, spot_3;

bool str_comp(string &s1, string &s2)
{
    return s1.length() < s2.length();
}

void push_to_type(string &s)
{
    if (s.length() % 2 == 1)
        type1.pb(s);
    else {
        if (s[0] == 'A')
            type2.pb(s);
        else    
            type3.pb(s);
    }

    s.clear();
    return;
}

void success(void)
{
    printf("YES\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        type1.clear();
        pairs_remaining_2 = pairs_remaining_3 = 0;
        spot_2 = spot_3 = -1;
        type2.clear();
        type3.clear();

        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        getchar();
        int n = a + b + 2 * c + 2 * d;

        string word;
        int a_num = 0;
        char e;
        for (int i = 0; i < n; i++) {
            e = getchar();
            word.pb(e);
            if (word[i] == 'A')
                a_num++;
        }

        if (a_num != a + c + d) {
            printf("NO\n");
            continue;
        }

        string nstr;
        nstr.pb(word[0]);
        for (int i = 1; i < n; i++) {
            if (word[i] == nstr.back()) {
                push_to_type(nstr);
            }
            nstr.pb(word[i]);
        }
        push_to_type(nstr);

        sort(type2.begin(), type2.end(), str_comp);
        sort(type3.begin(), type3.end(), str_comp);

        for (int i = 0; i < type2.size(); i++) {
            int pos = type2[i].length() / 2;
            if (pos < c) 
                c -= pos;
            else {
                pairs_remaining_2 = max(pos - c - 1, 0);
                c = 0;
                spot_2 = i;
                break;
            }
        }
        for (int i = 0; i < type3.size(); i++) {
            int pos = type3[i].length() / 2;
            if (pos < d)
                d -= pos;
            else {
                pairs_remaining_3 = max(pos - d - 1, 0);
                d = 0;
                spot_3 = i;
                break;
            }
        }


        if (spot_2 != -1) {
            d -= pairs_remaining_2;
            
            for (int i = spot_2 + 1; i < type2.size(); i++) {
                d -= (type2[i].length() / 2 )- 1;
            }
            if (d <= 0) {
                success();
                continue;
            }
        }
        else if (spot_3 != -1) {
            c -= pairs_remaining_3;

            for (int i = spot_3 + 1; i < type3.size(); i++) {
                c -= (type3[i].length() / 2) - 1;
            }
            if (c <= 0) {
                success();
                continue;
            }
        }

        int j = 0;
        while (c > 0 && j < type1.size()) {
            int pos = type1[j].length() / 2;
            if (c > pos) {
                c -= pos;
            }
            else {
                d -= pos - c;
                c = 0;
            }

            j++;
        }
        while (d > 0 && j < type1.size()) {
            d -= type1[j].length() / 2;
            j++;
        }


        if (c <= 0 && d <= 0) {
            success();
            continue;
        }

        printf("NO\n");
    }
}