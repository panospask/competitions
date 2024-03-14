#include <bits/stdc++.h>

using namespace std;

string s, t;
int n;
bool iseq[100005]; 

bool check_for_good(int i)
{
    if (i == n)
        return false;

    char first = s[i], sec = s[i + 1];

    if (first == 'a' && sec == 'b') {
        if (t[i] == 'b') {
            swap(s[i], s[i + 1]);
            return true;
        }
        else 
            return false;
    }
    if (first == 'b' && sec == 'c') {
        if (t[i] == 'c') {
            swap(s[i], s[i + 1]);
            return true;
        }
        else 
            return false;
    }

    return false;
}

int main(void)
{
    int m;
    scanf("%d", &m);

    for (int x = 0; x < m; x++) {
        scanf("%d", &n);
        getchar();
        memset(iseq, false, n);
        s.clear(); t.clear();
        s.resize(n); t.resize(n);

        for (int i = 0; i < n; i++) 
            s[i] = getchar();
        getchar();
        for (int i = 0; i < n; i++) 
            t[i] = getchar();

        for (int i = 0; i < n; i++)
            if (s[i] == t[i])
                iseq[i] = true;

        bool can_fix = true;
        for (int i = 0; i < n && can_fix; i++) {
            if (s[i] != t[i]) {
                can_fix = check_for_good(i);
            }
        }

        if (can_fix)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}